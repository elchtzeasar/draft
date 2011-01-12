TARGET = remote_controller

! include( ../../common.pri ) {
    error( Couldnt find the common.pri file! )
}

! include( ../include/files.pri ) {
    error( Couldnt find the public_files.pri file! )
}

! include( ../src/files.pri ) {
    error( Couldnt find the private_files.pri file! )
}

