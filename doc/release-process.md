Release Process
====================

Before every release candidate:

* Update translations (ping wumpus on IRC) see [translation_process.md](https://github.com/liquidcashproject/Titan/blob/master/doc/translation_process.md#synchronising-translations).

* Update manpages, see [gen-manpages.sh](https://github.com/liquidcashproject/Titan/blob/master/contrib/devtools/README.md#gen-manpagessh).

Before every minor and major release:

* Update [bips.md](bips.md) to account for changes since the last release.
* Update version in `configure.ac` (don't forget to set `CLIENT_VERSION_IS_RELEASE` to `true`)
* Write release notes (see below)
* Update `src/chainparams.cpp` nMinimumChainWork with information from the getblockchaininfo rpc.
* Update `src/chainparams.cpp` defaultAssumeValid  with information from the getblockhash rpc.
  - The selected value must not be orphaned so it may be useful to set the value two blocks back from the tip.
  - Testnet should be set some tens of thousands back from the tip due to reorgs there.
  - This update should be reviewed with a reindex-chainstate with assumevalid=0 to catch any defect
     that causes rejection of blocks in the past history.

Before every major release:

* Update hardcoded [seeds](/contrib/seeds/README.md), see [this pull request](https://github.com/liquidcashproject/Titan/pull/7415) for an example.
* Update [`BLOCK_CHAIN_SIZE`](/src/qt/intro.cpp) to the current size plus some overhead.
* Update `src/chainparams.cpp` chainTxData with statistics about the transaction count and rate.
* Update version of `contrib/gitian-descriptors/*.yml`: usually one'd want to do this on master after branching off the release - but be sure to at least do it before a new major release

### First time / New builders

If you're using the automated script (found in [contrib/gitian-build.sh](/contrib/gitian-build.sh)), then at this point you should run it with the "--setup" command. Otherwise ignore this.

Check out the source code in the following directory hierarchy.

    cd /path/to/your/toplevel/build
    git clone https://github.com/liquidcash-core/gitian.sigs.git
    git clone https://github.com/liquidcash-core/liquidcash-detached-sigs.git
    git clone https://github.com/devrandom/gitian-builder.git
    git clone https://github.com/liquidcashproject/Titan.git

### Liquidcash maintainers/release engineers, suggestion for writing release notes

Write release notes. git shortlog helps a lot, for example:

    git shortlog --no-merges v(current version, e.g. 0.7.2)..v(new version, e.g. 0.8.0)

(or ping @wumpus on IRC, he has specific tooling to generate the list of merged pulls
and sort them into categories based on labels)

Generate list of authors:

    git log --format='%aN' "$*" | sort -ui | sed -e 's/^/- /'

Tag version (or release candidate) in git

    git tag -s v(new version, e.g. 0.8.0)

### Setup and perform Gitian builds

If you're using the automated script (found in [contrib/gitian-build.sh](/contrib/gitian-build.sh)), then at this point you should run it with the "--build" command. Otherwise ignore this.

Setup Gitian descriptors:

    pushd ./liquidcash
    export SIGNER=(your Gitian key, ie bluematt, sipa, etc)
    export VERSION=(new version, e.g. 0.8.0)
    git fetch
    git checkout v${VERSION}
    popd

Ensure your gitian.sigs are up-to-date if you wish to gverify your builds against other Gitian signatures.

    pushd ./gitian.sigs
    git pull
    popd

Ensure gitian-builder is up-to-date:

    pushd ./gitian-builder
    git pull
    popd

### Fetch and create inputs: (first time, or when dependency versions change)

    pushd ./gitian-builder
    mkdir -p inputs
    wget -P inputs https://titanprojects.co/cfields/osslsigncode-Backports-to-1.7.1.patch
    wget -P inputs http://downloads.sourceforge.net/project/osslsigncode/osslsigncode/osslsigncode-1.7.1.tar.gz
    popd

Create the OS X SDK tarball, see the [OS X readme](README_osx.md) for details, and copy it into the inputs directory.

### Optional: Seed the Gitian sources cache and offline git repositories

By default, Gitian will fetch source files as needed. To cache them ahead of time:

    pushd ./gitian-builder
    make -C ../liquidcash/depends download SOURCES_PATH=`pwd`/cache/common
    popd

Only missing files will be fetched, so this is safe to re-run for each build.

NOTE: Offline builds must use the --url flag to ensure Gitian fetches only from local URLs. For example:

    pushd ./gitian-builder
    ./bin/gbuild --url liquidcash=/path/to/liquidcash,signature=/path/to/sigs {rest of arguments}
    popd

The gbuild invocations below <b>DO NOT DO THIS</b> by default.

### Build and sign Liquidcash Core for Linux, Windows, and OS X:

    pushd ./gitian-builder
    ./bin/gbuild --num-make 2 --memory 3000 --commit liquidcash=v${VERSION} ../liquidcash/contrib/gitian-descriptors/gitian-linux.yml
    ./bin/gsign --signer $SIGNER --release ${VERSION}-linux --destination ../gitian.sigs/ ../liquidcash/contrib/gitian-descriptors/gitian-linux.yml
    mv build/out/liquidcash-*.tar.gz build/out/src/liquidcash-*.tar.gz ../

    ./bin/gbuild --num-make 2 --memory 3000 --commit liquidcash=v${VERSION} ../liquidcash/contrib/gitian-descriptors/gitian-win.yml
    ./bin/gsign --signer $SIGNER --release ${VERSION}-win-unsigned --destination ../gitian.sigs/ ../liquidcash/contrib/gitian-descriptors/gitian-win.yml
    mv build/out/liquidcash-*-win-unsigned.tar.gz inputs/liquidcash-win-unsigned.tar.gz
    mv build/out/liquidcash-*.zip build/out/liquidcash-*.exe ../

    ./bin/gbuild --num-make 2 --memory 3000 --commit liquidcash=v${VERSION} ../liquidcash/contrib/gitian-descriptors/gitian-osx.yml
    ./bin/gsign --signer $SIGNER --release ${VERSION}-osx-unsigned --destination ../gitian.sigs/ ../liquidcash/contrib/gitian-descriptors/gitian-osx.yml
    mv build/out/liquidcash-*-osx-unsigned.tar.gz inputs/liquidcash-osx-unsigned.tar.gz
    mv build/out/liquidcash-*.tar.gz build/out/liquidcash-*.dmg ../
    popd

Build output expected:

  1. source tarball (`liquidcash-${VERSION}.tar.gz`)
  2. linux 32-bit and 64-bit dist tarballs (`liquidcash-${VERSION}-linux[32|64].tar.gz`)
  3. windows 32-bit and 64-bit unsigned installers and dist zips (`liquidcash-${VERSION}-win[32|64]-setup-unsigned.exe`, `liquidcash-${VERSION}-win[32|64].zip`)
  4. OS X unsigned installer and dist tarball (`liquidcash-${VERSION}-osx-unsigned.dmg`, `liquidcash-${VERSION}-osx64.tar.gz`)
  5. Gitian signatures (in `gitian.sigs/${VERSION}-<linux|{win,osx}-unsigned>/(your Gitian key)/`)

### Verify other gitian builders signatures to your own. (Optional)

Add other gitian builders keys to your gpg keyring, and/or refresh keys.

    gpg --import liquidcash/contrib/gitian-keys/*.pgp
    gpg --refresh-keys

Verify the signatures

    pushd ./gitian-builder
    ./bin/gverify -v -d ../gitian.sigs/ -r ${VERSION}-linux ../liquidcash/contrib/gitian-descriptors/gitian-linux.yml
    ./bin/gverify -v -d ../gitian.sigs/ -r ${VERSION}-win-unsigned ../liquidcash/contrib/gitian-descriptors/gitian-win.yml
    ./bin/gverify -v -d ../gitian.sigs/ -r ${VERSION}-osx-unsigned ../liquidcash/contrib/gitian-descriptors/gitian-osx.yml
    popd

### Next steps:

Commit your signature to gitian.sigs:

    pushd gitian.sigs
    git add ${VERSION}-linux/${SIGNER}
    git add ${VERSION}-win-unsigned/${SIGNER}
    git add ${VERSION}-osx-unsigned/${SIGNER}
    git commit -a
    git push  # Assuming you can push to the gitian.sigs tree
    popd

Codesigner only: Create Windows/OS X detached signatures:
- Only one person handles codesigning. Everyone else should skip to the next step.
- Only once the Windows/OS X builds each have 3 matching signatures may they be signed with their respective release keys.

Codesigner only: Sign the osx binary:

    transfer liquidcash-osx-unsigned.tar.gz to osx for signing
    tar xf liquidcash-osx-unsigned.tar.gz
    ./detached-sig-create.sh -s "Key ID"
    Enter the keychain password and authorize the signature
    Move signature-osx.tar.gz back to the gitian host

Codesigner only: Sign the windows binaries:

    tar xf liquidcash-win-unsigned.tar.gz
    ./detached-sig-create.sh -key /path/to/codesign.key
    Enter the passphrase for the key when prompted
    signature-win.tar.gz will be created

Codesigner only: Commit the detached codesign payloads:

    cd ~/liquidcash-detached-sigs
    checkout the appropriate branch for this release series
    rm -rf *
    tar xf signature-osx.tar.gz
    tar xf signature-win.tar.gz
    git add -a
    git commit -m "point to ${VERSION}"
    git tag -s v${VERSION} HEAD
    git push the current branch and new tag

Non-codesigners: wait for Windows/OS X detached signatures:

- Once the Windows/OS X builds each have 3 matching signatures, they will be signed with their respective release keys.
- Detached signatures will then be committed to the [liquidcash-detached-sigs](https://github.com/liquidcash-core/liquidcash-detached-sigs) repository, which can be combined with the unsigned apps to create signed binaries.

Create (and optionally verify) the signed OS X binary:

    pushd ./gitian-builder
    ./bin/gbuild -i --commit signature=v${VERSION} ../liquidcash/contrib/gitian-descriptors/gitian-osx-signer.yml
    ./bin/gsign --signer $SIGNER --release ${VERSION}-osx-signed --destination ../gitian.sigs/ ../liquidcash/contrib/gitian-descriptors/gitian-osx-signer.yml
    ./bin/gverify -v -d ../gitian.sigs/ -r ${VERSION}-osx-signed ../liquidcash/contrib/gitian-descriptors/gitian-osx-signer.yml
    mv build/out/liquidcash-osx-signed.dmg ../liquidcash-${VERSION}-osx.dmg
    popd

Create (and optionally verify) the signed Windows binaries:

    pushd ./gitian-builder
    ./bin/gbuild -i --commit signature=v${VERSION} ../liquidcash/contrib/gitian-descriptors/gitian-win-signer.yml
    ./bin/gsign --signer $SIGNER --release ${VERSION}-win-signed --destination ../gitian.sigs/ ../liquidcash/contrib/gitian-descriptors/gitian-win-signer.yml
    ./bin/gverify -v -d ../gitian.sigs/ -r ${VERSION}-win-signed ../liquidcash/contrib/gitian-descriptors/gitian-win-signer.yml
    mv build/out/liquidcash-*win64-setup.exe ../liquidcash-${VERSION}-win64-setup.exe
    mv build/out/liquidcash-*win32-setup.exe ../liquidcash-${VERSION}-win32-setup.exe
    popd

Commit your signature for the signed OS X/Windows binaries:

    pushd gitian.sigs
    git add ${VERSION}-osx-signed/${SIGNER}
    git add ${VERSION}-win-signed/${SIGNER}
    git commit -a
    git push  # Assuming you can push to the gitian.sigs tree
    popd

### After 3 or more people have gitian-built and their results match:

- Create `SHA256SUMS.asc` for the builds, and GPG-sign it:

```bash
sha256sum * > SHA256SUMS
```

The list of files should be:
```
liquidcash-${VERSION}-aarch64-linux-gnu.tar.gz
liquidcash-${VERSION}-arm-linux-gnueabihf.tar.gz
liquidcash-${VERSION}-i686-pc-linux-gnu.tar.gz
liquidcash-${VERSION}-x86_64-linux-gnu.tar.gz
liquidcash-${VERSION}-osx64.tar.gz
liquidcash-${VERSION}-osx.dmg
liquidcash-${VERSION}.tar.gz
liquidcash-${VERSION}-win32-setup.exe
liquidcash-${VERSION}-win32.zip
liquidcash-${VERSION}-win64-setup.exe
liquidcash-${VERSION}-win64.zip
```
The `*-debug*` files generated by the gitian build contain debug symbols
for troubleshooting by developers. It is assumed that anyone that is interested
in debugging can run gitian to generate the files for themselves. To avoid
end-user confusion about which file to pick, as well as save storage
space *do not upload these to the titanprojects.co server, nor put them in the torrent*.

- GPG-sign it, delete the unsigned file:
```
gpg --digest-algo sha256 --clearsign SHA256SUMS # outputs SHA256SUMS.asc
rm SHA256SUMS
```
(the digest algorithm is forced to sha256 to avoid confusion of the `Hash:` header that GPG adds with the SHA256 used for the files)
Note: check that SHA256SUMS itself doesn't end up in SHA256SUMS, which is a spurious/nonsensical entry.

- Upload zips and installers, as well as `SHA256SUMS.asc` from last step, to the titanprojects.co server
  into `/var/www/bin/liquidcash-core-${VERSION}`

- A `.torrent` will appear in the directory after a few minutes. Optionally help seed this torrent. To get the `magnet:` URI use:
```bash
transmission-show -m <torrent file>
```
Insert the magnet URI into the announcement sent to mailing lists. This permits
people without access to `titanprojects.co` to download the binary distribution.
Also put it into the `optional_magnetlink:` slot in the YAML file for
titanprojects.co (see below for titanprojects.co update instructions).

- Update titanprojects.co version

  - First, check to see if the titanprojects.co maintainers have prepared a
    release: https://github.com/liquidcash-dot-org/titanprojects.co/labels/Releases

      - If they have, it will have previously failed their Travis CI
        checks because the final release files weren't uploaded.
        Trigger a Travis CI rebuild---if it passes, merge.

  - If they have not prepared a release, follow the titanprojects.co release
    instructions: https://github.com/liquidcash-dot-org/titanprojects.co#release-notes

  - After the pull request is merged, the website will automatically show the newest version within 15 minutes, as well
    as update the OS download links. Ping @saivann/@harding (saivann/harding on Freenode) in case anything goes wrong

- Announce the release:

  - liquidcash-dev and liquidcash-core-dev mailing list

  - Liquidcash Core announcements list https://titanprojects.co/en/list/announcements/join/

  - liquidcashcore.org blog post

  - Update title of #liquidcash on Freenode IRC

  - Optionally twitter, reddit /r/Liquidcash, ... but this will usually sort out itself

  - Notify BlueMatt so that he can start building [the PPAs](https://launchpad.net/~liquidcash/+archive/ubuntu/liquidcash)

  - Archive release notes for the new version to `doc/release-notes/` (branch `master` and branch of the release)

  - Create a [new GitHub release](https://github.com/liquidcashproject/Titan/releases/new) with a link to the archived release notes.

  - Celebrate
