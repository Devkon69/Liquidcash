#!/bin/sh

TOPDIR=${TOPDIR:-$(git rev-parse --show-toplevel)}
SRCDIR=${SRCDIR:-$TOPDIR/src}
MANDIR=${MANDIR:-$TOPDIR/doc/man}

LCASHD=${LCASHD:-$SRCDIR/liquidcashd}
LCASHCLI=${LCASHCLI:-$SRCDIR/liquidcash-cli}
LCASHTX=${LCASHTX:-$SRCDIR/liquidcash-tx}
LCASHQT=${LCASHQT:-$SRCDIR/qt/liquidcash-qt}

[ ! -x $LCASHD ] && echo "$LCASHD not found or not executable." && exit 1

# The autodetected version git tag can screw up manpage output a little bit
LCASHVER=($($LCASHCLI --version | head -n1 | awk -F'[ -]' '{ print $6, $7 }'))

# Create a footer file with copyright content.
# This gets autodetected fine for liquidcashd if --version-string is not set,
# but has different outcomes for liquidcash-qt and liquidcash-cli.
echo "[COPYRIGHT]" > footer.h2m
$LCASHD --version | sed -n '1!p' >> footer.h2m

for cmd in $LCASHD $LCASHCLI $LCASHTX $LCASHQT; do
  cmdname="${cmd##*/}"
  help2man -N --version-string=${LCASHVER[0]} --include=footer.h2m -o ${MANDIR}/${cmdname}.1 ${cmd}
  sed -i "s/\\\-${LCASHVER[1]}//g" ${MANDIR}/${cmdname}.1
done

rm -f footer.h2m
