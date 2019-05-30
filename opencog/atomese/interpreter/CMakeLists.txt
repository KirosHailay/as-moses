#install header files
ADD_LIBRARY (condlink_interpreter SHARED
		condlink_interpreter
		)

TARGET_LINK_LIBRARIES(condlink_interpreter
		asmoses_exec
		)


INSTALL(FILES

		Interpreter.h
		logical_interpreter.h
		condlink_interpreter.h

		DESTINATION

		"include/opencog/${PROJECT_NAME}/atomese/interpreter"
		)
