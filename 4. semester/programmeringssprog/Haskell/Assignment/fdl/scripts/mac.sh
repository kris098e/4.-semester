#!/bin/bash
/bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"
brew install ghc libx11 libxrandr libxscrnsaver cabal-install
cabal update
cabal install --lib HGL
ghci -XNPlusKPatterns fdl.hs -e 'runGraphics (withWindow_ "Test" (1000, 600) (\ w -> drawIt (w, 500, 300, 0, 50) [Forward, RightTurn 90, Forward, RightTurn 90, Forward, RightTurn 90, Forward] >> getKey w))'
