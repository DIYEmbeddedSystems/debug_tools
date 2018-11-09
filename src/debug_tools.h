/** @file debug_tools.h
 * 
 * @brief The debug_tools header provides various macros useful to software 
 * debugging activities.Provided macros allow to print out various messages, 
 * depending on current debugging level:
 *  INFO(message, ...)
 *  DEBUG(message, ...)
 *  WARNING(message, ...)
 *  ERROR(message, ...)
 * The message and additional parameters are printf-syntax formatting arguments.
 * 
 * Also provided is a tracing macro, which counts and prints out how many
 * times your program runs a particular line of code:
 *  TRACE()
 *  TRACE_MSG(message, ...)
 * 
 * @author Etienne Hamelin
 */

#ifndef DEBUG_TOOLS_H
#define DEBUG_TOOLS_H


/**
 * @brief this macro returns the file name and compilation timestamp 
 */
#define FILE_INFO   "File " __FILE__ " compiled " __TIMESTAMP__ "."

/**
 * @brief Definition of debugging levels: NONE, ERROR, WARNING, DEBUG, INFO = ALL
 * When DBG_LEVEL is defined to DBG_LVL_ALL, then all debugging macros will 
 * effectively print out their message. By reducing DBG_LEVEL you can select 
 * how much debugging information is effectively printed out. If DBG_LEVEL is 
 * set to 0, then no debugging information is printed out. 
 */
#define DBG_LVL_NONE 0
#define DBG_LVL_ERROR 1
#define DBG_LVL_WARNING 2
#define DBG_LVL_DEBUG 3
#define DBG_LVL_INFO 4
#define DBG_LVL_ALL DBG_LVL_INFO

/**
 * @brief By default, debug level = INFO
 */
#ifndef DBG_LEVEL
	#define DBG_LEVEL DBG_LVL_ALL
#endif

/**
 * @brief Token concatenation macros
 */
#define _CAT(tok1, tok2) tok1##tok2
#define CAT(tok1, tok2) _CAT(tok1, tok2)

/**
 * @brief Create a (quasi-)unique identifier based on a common prefix, and the current line in file
 */
#define UNIQUE_ID(prefix) CAT(prefix, __LINE__)


#if DBG_LEVEL >= DBG_LVL_ERROR
/**
 * @brief Generic debugging information message formatter
 * @param file : the file to use for outputting (typically stdout or stderr)
 * @param info : short indication of the type of information (typically "ERROR", "INFO" etc.)
 * @param message, ... : printf-syntax format string and additional parameters for user-specified message 
 */
    #define DBG_MSG(file, info, message, ...) \
	    do { \
		    fprintf(file, "[%s] %s at %s:%d :\t " message "\n",\
			    info, __PRETTY_FUNCTION__, __FILE__, (int) __LINE__, ##__VA_ARGS__); \
    	} while(0)

/**
 * @brief Error message
 * @param message, ... : printf-syntax format string and additional parameters for user-specified message
 */
	#define ERROR(...) 	DBG_MSG(stderr, "ERROR", ##__VA_ARGS__)        
#else
/**
 * If debugging is disabled, macros are reduced to void
 */ 
    #define DBG_MSG(...)
    #define ERROR(...)
#endif

#if (DBG_LEVEL >= DBG_LVL_INFO)
/**
 * @brief Print out information message
 * @param message, ... : printf-syntax format string and additional parameters for user-specified message 
 */
	#define INFO(...)	DBG_MSG(stdout, "INFO", ##__VA_ARGS__)
#else 
	#define INFO(...)
#endif 

#if (DBG_LEVEL >= DBG_LVL_DEBUG)
/**
 * @brief Print out debugging information message
 * @param message, ... : printf-syntax format string and additional parameters for user-specified message 
 */
	#define DEBUG(...) 	DBG_MSG(stdout, "DEBUG", ##__VA_ARGS__)
#else
	#define DEBUG(...)
#endif 

#if (DBG_LEVEL >= DBG_LVL_WARNING)
/**
 * @brief Print out warning message
 * @param message, ... : printf-syntax format string and additional parameters for user-specified message 
 */
	#define WARNING(...) 	DBG_MSG(stdout, "WARNING", ##__VA_ARGS__)
#else
	#define WARNING(...)
#endif



#if (DBG_LEVEL >= DBG_LVL_INFO)
/**
 * @brief Tracing point
 * Counts and prints out how many times your code runs through this point. 
 */
    #define TRACE(...) \
        do { \
            static int UNIQUE_ID(trace_counter_) = 0; \
            ++UNIQUE_ID(trace_counter_); \
            DBG_MSG(stdout, "TRACE", "count = %d", (int)UNIQUE_ID(trace_counter_)); \
        } while (0)
    
/**
 * @brief Tracing point with user-specified message
 * Counts and prints out how many times your code runs through this point, as well as user-specified message
 * @param message, ... : printf-syntax format string and additional parameters 
 */
    #define TRACE_MSG(message, ...) \
        do { \
            static int UNIQUE_ID(trace_counter_) = 0; \
            ++UNIQUE_ID(trace_counter_); \
            DBG_MSG(stdout, "TRACE", "count = %d :\t " message, (int)UNIQUE_ID(trace_counter_), ##__VA_ARGS__); \
        } while (0)

#else 
	#define TRACE(...)
    #define TRACE_MSG(message, ...)
#endif 

#endif /* DEBUG_TOOLS_H */
