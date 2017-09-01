#!/bin/bash

VERS=0.9
USER=`whoami`

# Need a build
if [[ ! -r "../namegen" ]] ; then
	echo build ../namegen
	exit
fi

# Set up directories
rm -rf deb
mkdir -p deb/namegen-$VERS/DEBIAN/ deb/namegen-$VERS/usr/bin deb/namegen-$VERS/usr/share/icons/hicolor deb/namegen-$VERS/usr/share/applications

# Add Debian package stuff
cp conffiles control deb/namegen-$VERS/DEBIAN/.

# Icons
ls icons | sed 's/\/// ; s/\.png// ; s/namegen_//' | while read dims ; do
	mkdir -p deb/namegen-$VERS/usr/share/icons/hicolor/$dims/apps
	#echo cp ./icons/namegen_$dims.png deb/namegen-$VERS/usr/share/icons/hicolor/$dims/apps/namegen.png
	cp ./icons/namegen_$dims.png deb/namegen-$VERS/usr/share/icons/hicolor/$dims/apps/namegen.png
done

# Add the build
cp ../namegen deb/namegen-$VERS/usr/bin/.

# Desktop
cp namegen.desktop deb/namegen-$VERS/usr/share/applications/.

# Fix the permissions
chmod -R 755 deb/namegen-$VERS/
chmod 644 deb/namegen-$VERS/DEBIAN/conffiles deb/namegen-$VERS/DEBIAN/control

# Change ownership to root
sudo chown -R root:root deb/namegen-$VERS/

# Build the package
sudo dpkg-deb --build deb/namegen-$VERS

# Revert the ownership from root
sudo chown -R $USER:$USER deb

# Move the package to the current directory
echo "moving deb/namegen-$VERS.deb to ./."
mv deb/namegen-$VERS.deb ./.

# Clean up

rm -rf deb
