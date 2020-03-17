# waft
Easy annotation of pupils for eye tracking algorithms.

## Usage
If you are working on Microsoft Windows, please just download the most recent release. Otherwise, please compile the C++ code using a decent version of CMake and Qt. After start just follow the dialog through the annotation process:
1. Please specify if you rather want to annotate new frames or open existing annotations. Afterward, click 'Load samples' and 'Commit' to proceed.
2. Please annotate the pupil in the following frames. Click anywhere in the image to set the center of the ellipsis. Use your mouse wheel to rotate. Using SHIFT + mouse wheel will scale the mayor axis, while utilizing CTLR + mouse wheel will scale the minor one.
3. At the end, please specify the file the annotated pupils are saved in. If choosing an existing file, you may overwrite it or append the new annotations.

## File format
Waft utilizes a rather simple format for exchange of pupil data: A *.tsv file is just a *.csv file with tabs as separator. An example looks like this:

| file             | x        | y        | major     | minor     | rotation |
|------------------|----------|----------|-----------|-----------|----------|
| 1_frame_2057.png | 0.735714 | 0.387952 | 0.0583333 | 0.0447917 | 210      |
| 1_frame_3972.png | 0.458333 | 0.456627 | 0.0447917 | 0.0375    | 36       |

Keep in mind that this format is not(!) directly usable i.e. with Pupil Labs. **file** specifies the path of a video frame relative to the *.tsv file. The **x** value is a float between 0-1 relative to the width of the frame, while **y** is relative to its height. Similar, the **major** and **minor** axis are relative to *max(width, height)*. Finally, the rotation is measured in degrees.
