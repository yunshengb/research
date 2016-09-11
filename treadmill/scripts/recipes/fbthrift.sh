#!/usr/bin/env bash

source common.sh

[ -d fbthrift ] || git clone https://github.com/facebook/fbthrift

cd "$PKG_DIR/fbthrift/thrift" || die "cd fbthrift failed"
git checkout d811b530a4f5e11a520f5fb416a5a3a8a5f42ef8
autoreconf --install
LD_LIBRARY_PATH="$INSTALL_DIR/lib:$LD_LIBRARY_PATH" \
  LD_RUN_PATH="$INSTALL_DIR/lib:$LD_RUN_PATH" \
  ./configure --prefix="$INSTALL_DIR" --bindir="$INSTALL_AUX_DIR/bin" \
              PY_PREFIX="$INSTALL_AUX_DIR" \
              PY_INSTALL_HOME="$INSTALL_AUX_DIR" \
              --with-folly="$INSTALL_DIR" && \
  make $MAKE_ARGS && make install $MAKE_ARGS
