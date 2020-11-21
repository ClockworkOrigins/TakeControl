@echo OFF

IF "%1" == "build" (goto build)

call build-common.bat %1 %2

call build-gmock.bat build %1 %2 Debug
call build-gmock.bat build %1 %2 Release

EXIT /B

:build

Set ARCHIVE=release-1.10.0.zip
Set BUILD_DIR=%TMP_DIR%/googletest-release-1.10.0
Set PREFIX=%DEP_DIR%/%ARCH_DIR%/gmock/%4

IF EXIST %PREFIX% EXIT /B

echo "Compile GoogleMock with GoogleTest"

echo "Extracting GoogleMock with GoogleTest"

call build-common.bat downloadAndUnpack %ARCHIVE% %BUILD_DIR% https://github.com/google/googletest/archive/

echo "Configuring GoogleMock with GoogleTest"

cd %BUILD_DIR%
cmake -DCMAKE_INSTALL_PREFIX=%PREFIX% -DBUILD_SHARED_LIBS=ON -G "%VSCOMPILER%" -A "%VSARCH%" .

echo "Building GoogleMock with GoogleTest"

cmake --build . --config %4

echo "Installing GoogleMock with GoogleTest"

cmake --build . --config %4 --target install

echo "Cleaning up"

cd %DEP_DIR%
RD /S /Q "%TMP_DIR%"

EXIT /B 0
