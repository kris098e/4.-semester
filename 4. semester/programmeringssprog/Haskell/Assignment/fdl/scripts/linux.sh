#!/bin/bash
sudo apt-get update
sudo apt-get install ghc cabal-install
cabal update
cabal install --lib HGL
ghci -XNPlusKPatterns fdl.hs -e 'runGraphics (withWindow_ "Test" (1000, 600) (\ w -> drawIt (w, 500, 300, 0, 50) [Forward, RightTurn 90, Forward, RightTurn 90, Forward, RightTurn 90, Forward] >> getKey w))'
