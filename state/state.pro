! include( ../common.pri ) {
    error( Couldnt find the common.pri file! )
}

INCLUDEPATH += src/client src/server

! include( public_files.pri ) {
    error( Couldnt find the public_files.pri file! )
}

! include( private_files.pri ) {
    error( Couldnt find the private_files.pri file! )
}
