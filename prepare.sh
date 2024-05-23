#!/usr/bin/env bash
wget http://ftp.freebsd.org/pub/FreeBSD/releases/amd64/13.2-RELEASE/base.txz
aunpack base.txz
rm -rf base/bin/
rm -rf base/sbin/
rm -rf base/var/
rm -rf base/boot/
rm -rf base/rescue/
rm -rf base/usr/bin/
rm -rf base/usr/sbin/
rm -rf base/usr/tests/
rm -rf base/usr/share/
rm -rf base/usr/lib/clang/
