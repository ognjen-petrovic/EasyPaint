EasyPaint
=========

I needed simple program that can take a screenshot and do simple edits.
Original project is [here](https://github.com/Gr1N/EasyPaint).

My additions to original:

* Screnshot
* Crop
* Arrow instrument

Windows program download: [easypaint_Qt_5_9_1_MinGW_32bit.zip](https://bintray.com/ognjen-petrovic/EasyPaint/download_file?file_path=easypaint_Qt_5_9_1_MinGW_32bit.zip).


Installing
----------

Install EasyPaint using the commands, if you use CMake:

    cd ./EasyPaint
    cmake -DCMAKE_INSTALL_PREFIX=/usr
    make
    make install

Install EasyPaint using the commands, if you use qmake:

    cd ./EasyPaint/sources
    lrelease easypaint.pro
    qmake
    make
    make install

License
-------

EasyPaint is distributed under the [MIT license](http://www.opensource.org/licenses/MIT).
