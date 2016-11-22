In order to run on OS X you must use brew to download SFML. (I know it's retarded)
follow the snippet bellow and you’ll be fine

If you don't have home-brew install it by using the following line.
-/usr/bin/ruby -e "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/master/install)"

-brew install sfml

-cd /usr/local/lib

-rm libjpeg.dylib

-rm libPng.dylib

-ln -s /System/Library/Frameworks/ImageIO.framework/Resources/libJPEG.dylib libJPEG.dylib

-ln -s /System/Library/Frameworks/ImageIO.framework/Resources/libPng.dylib libPng.dylib
