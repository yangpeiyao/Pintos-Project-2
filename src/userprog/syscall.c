#include "userprog/syscall.h"
#include <stdio.h>
#include <syscall-nr.h>
#include "threads/interrupt.h"
#include "threads/thread.h"

static void syscall_handler (struct intr_frame *);

void
syscall_init (void) 
{
  intr_register_int (0x30, 3, INTR_ON, syscall_handler, "syscall");
}

static void
syscall_handler (struct intr_frame *f)
{
  void *esp = f->esp;
  int systemCallNumber = *(int *)esp;
  
  switch (systemCallNumber) {
    case SYS_HALT:
      halt();
      break;
      case SYS_EXIT: {
          int status = *(int *)(esp + 1);
          exit(status);
          break;
      }
    case SYS_EXEC:
      break;
    case SYS_WAIT:
      break;
      case SYS_CREATE: {
          const char *fileName = *(char *)(esp + 1);
          unsigned fileSize = *(unsigned *)(esp + 2);
          f->eax = create(fileName, fileSize);
          break;
      }
    case SYS_REMOVE:
      break;
    case SYS_OPEN:
      break;
    case SYS_FILESIZE:
      break;
    case SYS_READ:
      break;
    case SYS_WRITE:
      break;
    case SYS_SEEK:
      break;
    case SYS_TELL:
      break;
    case SYS_CLOSE:
      break;
    default:
      break;
  }
}

//Terminates Pintos by calling shutdown_power_off() (declared in threads/init.h). This should be seldom used, because you lose some information about possible deadlock situations, etc.
void halt (void) {
  shutdown_power_off();
}

//Terminates the current user program, returning status to the kernel. If the process's parent waits for it (see below), this is the status that will be returned. Conventionally, a status of 0 indicates success and nonzero values indicate errors.
void exit (int status) {
  thread_exit ();
}

//Runs the executable whose name is given in cmd_line, passing any given arguments, and returns the new process's program id (pid). Must return pid -1, which otherwise should not be a valid pid, if the program cannot load or run for any reason. Thus, the parent process cannot return from the exec until it knows whether the child process successfully loaded its executable. You must use appropriate synchronization to ensure this.
tid_t exec (const char *cmd_line) {

}

//Waits for a child process pid and retrieves the child's exit status. More in documentation on this
int wait (tid_t pid) {
  
}

//Creates a new file called file initially initial_size bytes in size. Returns true if successful, false otherwise. Creating a new file does not open it: opening the new file is a separate operation which would require a open system call.
bool create (const char *file, unsigned initial_size) {
    if (file == NULL) { return false; }
  return filesys_create(file, initial_size); //call filesys_create
}

//Deletes the file called file. Returns true if successful, false otherwise. A file may be removed regardless of whether it is open or closed, and removing an open file does not close it. See Removing an Open File, for details.
bool remove (const char *file) {
  if (file == NULL) {return false;}
  return filesys_remove (file);
}

//Opens the file called file. Returns a nonnegative integer handle called a "file descriptor" (fd), or -1 if the file could not be opened.
//File descriptors numbered 0 and 1 are reserved for the console: fd 0 (STDIN_FILENO) is standard input, fd 1 (STDOUT_FILENO) is standard output. The open system call will never return either of these file descriptors, which are valid as system call arguments only as explicitly described below.
int open (const char *file) {
  if (file == NULL) {return false;}
  int status = filesys_open (file);
  return status;
}

//Returns the size, in bytes, of the file open as fd.
int filesize (int fd) {
  
  
}

//Reads size bytes from the file open as fd into buffer. Returns the number of bytes actually read (0 at end of file), or -1 if the file could not be read (due to a condition other than end of file). Fd 0 reads from the keyboard using input_getc().
int read (int fd, void *buffer, unsigned size) {
  
}

//Writes size bytes from buffer to the open file fd. Returns the number of bytes actually written, which may be less than size if some bytes could not be written.
//Writing past end-of-file would normally extend the file, but file growth is not implemented by the basic file system. The expected behavior is to write as many bytes as possible up to end-of-file and return the actual number written, or 0 if no bytes could be written at all.
int write (int fd, const void *buffer, unsigned size) {
  
}

//Changes the next byte to be read or written in open file fd to position, expressed in bytes from the beginning of the file. (Thus, a position of 0 is the file's start.)
void seek (int fd, unsigned position) {
  
}

//Returns the position of the next byte to be read or written in open file fd, expressed in bytes from the beginning of the file.
unsigned tell (int fd) {
  
}

//Closes file descriptor fd. Exiting or terminating a process implicitly closes all its open file descriptors, as if by calling this function for each one.
void close (int fd) {
  
}