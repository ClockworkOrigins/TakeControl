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

function(LINK_TO_FOLDER sourceFolder destinationFolder)
	FILE(TO_NATIVE_PATH "${sourceFolder}" sourceFolderNative)
	FILE(TO_NATIVE_PATH "${destinationFolder}" destinationFolderNative)
	
	IF(NOT EXISTS "${destinationFolderNative}")	
		IF(WIN32)
			execute_process(COMMAND cmd /C mklink /d "${destinationFolderNative}" "${sourceFolderNative}")
		ELSE()
			execute_process(COMMAND ln -sfn "${sourceFolderNative}" "${destinationFolderNative}")
		ENDIF()
	ENDIF()
endfunction()
