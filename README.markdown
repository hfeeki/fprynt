Python Bindings for libfprint
=============================

Basic bindings for libfprint using boost::python. Currently support is only provided for enrollment and verification (I don't have access to an imaging/identification print reader.

Example:

    from fprynt import Reader, Fingers 

    reader = Reader()

    enrolled = reader.enrolled(Fingers.RightIndex) 
    while not enrolled:
        # atleast reader.enroll_stages loops
        enrolled = reader.enroll(Fingers.RightIndex)
        
    verified = reader.verify(Fingers.RightIndex)

Compilation:

    cd src_dir
    mkdir build
    cd build
    cmake ..
    make
    cd ..
    python example

