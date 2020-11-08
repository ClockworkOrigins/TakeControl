function(LINK_TO_FILE sourceFile destinationFile)
	FILE(TO_NATIVE_PATH "${sourceFile}" sourceFileNative)
	FILE(TO_NATIVE_PATH "${destinationFile}" destinationFileNative)
	
	IF(NOT EXISTS "${destinationFileNative}")	
		IF(WIN32)
			execute_process(COMMAND cmd /C mklink "${destinationFileNative}" "${sourceFileNative}")
		ELSE()
			execute_process(COMMAND ln -sfn "${sourceFileNative}" "${destinationFileNative}")
		ENDIF()
	ENDIF()
endfunction()