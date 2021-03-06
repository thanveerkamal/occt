// Created on: 1992-02-17
// Created by: Stephan GARNAUD
// Copyright (c) 1992-1999 Matra Datavision
// Copyright (c) 1999-2014 OPEN CASCADE SAS
//
// This file is part of Open CASCADE Technology software library.
//
// This library is free software; you can redistribute it and/or modify it under
// the terms of the GNU Lesser General Public License version 2.1 as published
// by the Free Software Foundation, with special exception defined in the file
// OCCT_LGPL_EXCEPTION.txt. Consult the file LICENSE_LGPL_21.txt included in OCCT
// distribution for complete text of the license and disclaimer of any warranty.
//
// Alternatively, this file may be used under the terms of Open CASCADE
// commercial license or contractual agreement.

#ifndef _OSD_File_HeaderFile
#define _OSD_File_HeaderFile

#include <Standard.hxx>
#include <Standard_DefineAlloc.hxx>
#include <Standard_Handle.hxx>

#include <Standard_Boolean.hxx>
#include <OSD_LockType.hxx>
#include <OSD_OpenMode.hxx>
#include <Standard_Integer.hxx>
#include <Standard_Address.hxx>
#include <OSD_FileNode.hxx>
#include <OSD_FromWhere.hxx>
#include <OSD_KindFile.hxx>
#include <Standard_Size.hxx>
class Standard_ProgramError;
class OSD_Path;
class OSD_Protection;
class TCollection_AsciiString;
class OSD_Printer;


//! Basic tools to manage files
//! Warning: 'ProgramError' is raised when somebody wants to use the methods
//! Read, Write, Seek, Close when File is not open.
class OSD_File  : public OSD_FileNode
{
public:

  DEFINE_STANDARD_ALLOC

  
  //! Creates File object.
  Standard_EXPORT OSD_File();
  
  //! Instantiates the object file, storing its name
  Standard_EXPORT OSD_File(const OSD_Path& Name);

  //! Unlocks and closes a file, deletes a descriptor and destructs a file object.
  Standard_EXPORT ~OSD_File();
  
  //! CREATES a file if it doesn't already exists or empties
  //! an existing file.
  //! After 'Build', the file is open.
  //! If no name was given, ProgramError is raised.
  Standard_EXPORT void Build (const OSD_OpenMode Mode, const OSD_Protection& Protect);
  
  //! Opens a File with specific attributes
  //! This works only on already existing file.
  //! If no name was given, ProgramError is raised.
  Standard_EXPORT void Open (const OSD_OpenMode Mode, const OSD_Protection& Protect);
  
  //! Appends data to an existing file.
  //! If file doesn't exist, creates it first.
  //! After 'Append', the file is open.
  //! If no name was given, ProgramError is raised.
  Standard_EXPORT void Append (const OSD_OpenMode Mode, const OSD_Protection& Protect);
  
  //! Attempts to read Nbyte bytes from the file associated with
  //! the object file.
  //! Upon successful completion, Read returns the number of
  //! bytes actually read and placed in the Buffer. This number
  //! may be less than Nbyte if the number of bytes left in the file
  //! is less than Nbyte bytes. In this case only number of read
  //! bytes will be placed in the buffer.
  Standard_EXPORT void Read (TCollection_AsciiString& Buffer, const Standard_Integer Nbyte);
  
  //! Reads bytes from the data pointed to by the object file
  //! into the buffer <Buffer>.
  //! Data is read until <NByte-1> bytes have been read,
  //! until	a newline character is read and transferred into
  //! <Buffer>, or until an EOF (End-of-File) condition is
  //! encountered.
  //! Upon successful completion, Read returns the number of
  //! bytes actually read into <NByteRead> and placed into the
  //! Buffer <Buffer>.
  Standard_EXPORT void ReadLine (TCollection_AsciiString& Buffer, const Standard_Integer NByte, Standard_Integer& NbyteRead);

  //! Reads bytes from the data pointed to by the object file
  //! into the buffer <Buffer>.
  //! Data is read until <NByte-1> bytes have been read,
  //! until	a newline character is read and transferred into
  //! <Buffer>, or until an EOF (End-of-File) condition is
  //! encountered.
  //! Upon successful completion, Read returns the number of
  //! bytes actually read and placed into the Buffer <Buffer>.
  inline Standard_Integer ReadLine (
    TCollection_AsciiString& Buffer, const Standard_Integer NByte) 
  {
    Standard_Integer NbyteRead;
    ReadLine(Buffer, NByte, NbyteRead);
    return NbyteRead;
  }

  
  //! Attempts to read Nbyte bytes from the files associated with
  //! the object File.
  //! Upon successful completion, Read returns the number of
  //! bytes actually read and placed in the Buffer. This number
  //! may be less than Nbyte if the number of bytes left in the file
  //! is less than Nbyte bytes. For this reason the output
  //! parameter Readbyte will contain the number of read bytes.
  Standard_EXPORT void Read (const Standard_Address Buffer, const Standard_Integer Nbyte, Standard_Integer& Readbyte);
  
  //! Attempts to write Nbyte bytes from the AsciiString to the file
  //! associated to the object File.
  Standard_EXPORT void Write (const TCollection_AsciiString& Buffer, const Standard_Integer Nbyte);
  
  //! Attempts to write Nbyte bytes from the buffer pointed
  //! to by Buffer to the file associated to the object File.
  Standard_EXPORT void Write (const Standard_Address Buffer, const Standard_Integer Nbyte);
  
  //! Sets the seek pointer associated with the open file
  Standard_EXPORT void Seek (const Standard_Integer Offset, const OSD_FromWhere Whence);
  
  //! Closes the file (and deletes a descriptor)
  Standard_EXPORT void Close();
  
  //! Returns TRUE if the seek pointer is at end of file.
  Standard_EXPORT Standard_Boolean IsAtEnd();
  
  //! Returns the kind of file. A file can be a
  //! file, a directory or a link.
  Standard_EXPORT OSD_KindFile KindOfFile() const;
  
  //! Makes a temporary File
  //! This temporary file is already open !
  Standard_EXPORT void BuildTemporary();
  
  //! Locks current file
  Standard_EXPORT void SetLock (const OSD_LockType Lock);
  
  //! Unlocks current file
  Standard_EXPORT void UnLock();
  
  //! Returns the current lock state
  Standard_EXPORT OSD_LockType GetLock();
  
  //! Returns TRUE if this file is locked.
  Standard_EXPORT Standard_Boolean IsLocked();
  
  //! Returns actual number of bytes of <me>.
  Standard_EXPORT Standard_Size Size();
  
  //! Prints a file on selected printer.
  Standard_EXPORT void Print (const OSD_Printer& WhichPrinter);
  
  //! Returns TRUE if <me> is open.
  Standard_EXPORT Standard_Boolean IsOpen() const;
  
  //! returns TRUE if the file exists and if the user
  //! has the autorization to read it.
  Standard_EXPORT Standard_Boolean IsReadable();
  
  //! returns TRUE if the file can be read and overwritten.
  Standard_EXPORT Standard_Boolean IsWriteable();
  
  //! returns TRUE if the file can be executed.
  Standard_EXPORT Standard_Boolean IsExecutable();
  
  //! Enables to emulate unix "tail -f" command.
  //! If a line is available in the file <me> returns it.
  //! Otherwise attemps to read again aNbTries times in the file
  //! waiting aDelay seconds between each read.
  //! If meanwhile the file increases returns the next line, otherwise
  //! returns FALSE.
  Standard_EXPORT Standard_Boolean ReadLastLine (TCollection_AsciiString& aLine, const Standard_Integer aDelay, const Standard_Integer aNbTries);
  
  //! find an editor on the system and edit the given file
  Standard_EXPORT Standard_Boolean Edit();

  //! Set file pointer position to the beginning of the file
  Standard_EXPORT void Rewind();

  //! Redirect a standard handle (fileno(stdout), fileno(stdin) or 
  //! fileno(stderr) to this OSD_File and return the copy of the original
  //! standard handle.
  //! Example:
  //!    OSD_File aTmp;
  //!    aTmp.BuildTemporary();
  //!    int stdfd = _fileno(stdout);
  //!
  //!    int oldout = aTmp.Capture(stdfd);
  //!    cout << "Some output to the file" << endl;
  //!    cout << flush;
  //!    fflush(stdout);
  //!
  //!    _dup2(oldout, stdfd); // Restore standard output
  //!    aTmp.Close();
  Standard_EXPORT int Capture(int theDescr);


protected:



  Standard_Integer myIO;
  Standard_Address myFILE;
  Standard_Integer myFileChannel;
  Standard_Address myFileHandle;


private:



  Standard_Boolean ImperativeFlag;
  OSD_LockType myLock;
  OSD_OpenMode myMode;


};







#endif // _OSD_File_HeaderFile
