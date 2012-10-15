find . -regex '.*\.\(h\|\cpp\|qml\|js\)' -exec grep --files-without-match 'Copyright' {} \; | grep -v build
