#!/bin/sh

# Creates application bundles for use on Mac OS X.

# Amazing simple little script by the guys from the glfw project
# http://glfw.sourceforge.net/

# I added the icon part (CFBundleIconFile) so that the app has a nice icon

if [ -z "$1" ]; then
  echo "usage: `basename $0` BUNDLE-NAME"
  exit 1
fi

bundle_name="$1"

if [ ! -d "${bundle_name}.app/Contents/MacOS" ]; then
  mkdir -p "${bundle_name}.app/Contents/MacOS"
fi

if [ ! -d "${bundle_name}.app/Contents/Resources" ]; then
  mkdir -p "${bundle_name}.app/Contents/Resources"
fi

if [ ! -f "${bundle_name}.app/Contents/PkgInfo" ]; then
  echo -n "APPL????" > "${bundle_name}.app/Contents/PkgInfo"
fi

if [ ! -f "${bundle_name}.app/Contents/Info.plist" ]; then
  cat > "${bundle_name}.app/Contents/Info.plist" <<EOF
<?xml version="1.0" encoding="UTF-8"?>
<!DOCTYPE plist PUBLIC "-//Apple Computer//DTD PLIST 1.0//EN" "http://www.apple.com/DTDs/PropertyList-1.0.dtd">
<plist version="1.0">
<dict>
        <key>CFBundleDevelopmentRegion</key>
        <string>English</string>
        <key>CFBundleExecutable</key>
        <string>${bundle_name}</string>
        <key>CFBundleIconFile</key>
		<string>icon.icns</string>
		<key>CFBundleInfoDictionaryVersion</key>
        <string>6.0</string>
        <key>CFBundlePackageType</key>
        <string>APPL</string>
        <key>CFBundleSignature</key>
        <string>????</string>
        <key>CFBundleVersion</key>
        <string>0.1</string>
</dict>
</plist>
EOF
fi
