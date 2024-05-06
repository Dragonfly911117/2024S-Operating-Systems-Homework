#!/bin/zsh

newHomeworkNo=$(($(find  . -maxdepth 1 -name 'HW*' -type d   | wc -l) + 1))
newDirectoryName="HW$newHomeworkNo"

mkdir $newDirectoryName || (echo "Error: Could not create directory $newDirectoryName" && exit 1)
cp -r template/* $newDirectoryName || (echo "Error: Could not copy files to $newDirectoryName" && exit 1)
echo "New homework directory created: $newDirectoryName"

cd $newDirectoryName || (echo "Error: Could not change directory to $newDirectoryName" && exit 1)
sed "s/project(HW)/project(HW$newHomeworkNo)/" CMakeLists.txt -i || (echo "Error: Could not modify CMakeLists.txt" && exit 1)
echo "Modified CMakeLists.txt to project(HW$newHomeworkNo)"

cd .. || (echo "Error: Could not change directory to .." && exit 1)
if [ -f "CMakeLists.txt" ]; then
    sed "\$a\\add_subdirectory(\"$newDirectoryName\""")" CMakeLists.txt -i || (echo "Error: Could not modify CMakeLists.txt" && exit 1)
    echo "Appended add_subdirectory(\"$newDirectoryName\") to CMakeLists.txt. "
else
    echo "Error: CMakeLists.txt not found"
fi

if [ -f "$newDirectoryName.pdf" ]; then
  echo "$newDirectoryName.pdf found, moving it to $newDirectoryName"
  mv "$newDirectoryName.pdf" "$newDirectoryName" || (echo "Error: Could not copy $newDirectoryName.pdf to $newDirectoryName" && exit 1)
else
  echo "$newDirectoryName.pdf not found"
fi