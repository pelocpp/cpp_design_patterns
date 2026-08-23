// ===========================================================================
// FileSystemVisitor.h // Visitor Pattern
// ===========================================================================

#pragma once

class File;
class Directory;

class FileSystemVisitor {
public:
    virtual ~FileSystemVisitor() = default;

    virtual void visit(File& file) = 0;
    virtual void visit(Directory& directory) = 0;
};

// ===========================================================================
// End-of-File
// ===========================================================================
