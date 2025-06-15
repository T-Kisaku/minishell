#ifndef MS_EXIT_STATUS_H
#define MS_EXIT_STATUS_H

#define EXIT_OK 0            // Success
#define EXIT_INTERNAL_ERR 1  // Internal error (e.g., malloc failure)
#define EXIT_USER_ERR 2      // User error (e.g., input or syntax error)
#define EXIT_EXEC_FAIL 126   // Execution failure (e.g., permission denied)
#define EXIT_NOT_FOUND 127   // Command not found
#define EXIT_SIGNAL_BASE 128 // Exit caused by signal (add signal number)

#endif // !MS_EXIT_STATUS_H
