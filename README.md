bnk\_pc\_extract & bnk\_pc\_pack
================================
Audio archives extractor and packer for .bnk_pc files in Volition games,
specifically Saints Row: The Third. I fixed up the code from my radio file
extractor and added support to extracting DMAV metadata included with voiced
soundclips. So far I've only actually tested this with the radio stations and
a couple voice acting sound banks, but it should work with all other files in
theory. Also have fun decoding the DMAV metadata, which contains subtitles
among other things.

How to use
----------
* Easy way: Drag and drop the *\_media.bnk\_pc files over bnk\_pc\_extractor,
  and it will extract all the sound files to the folder the *\_media.bnk\_pc
  file is in. (You might want to copy it to its own folder before dragging and
  dropping it.)
* Hard way/repacking files: Run the programs in the command line and follow
  the instructions it gives for the two programs.

How to make .wav files usable
-----------------------------
Download and run them through [ww2ogg](http://hcs64.com/vgm_ripping.html).
Make sure to pick up revorb from there too. Drag and drop the .wav over
ww2ogg, and the .ogg it makes over revorb.

How to make your own .wav files for packaging
---------------------------------------------
Follow steps 5-12 in my
[Custom Radio Stations Guide](https://www.saintsrowmods.com/forum/index.php?threads/custom-radio-stations-guide.2/).
Note that it's possible that other types of sounds use other settings than
those in the guide, but I'm pretty sure they all at least use Vorbis.

Changelog
---------
* 1.3
    * Made filelist appear in the metadata log, now you don't have to fuss
      with superlong command line arguments. Also fixes audiobank files with
      many files breaking in the Windows command prompt.
* 1.2
    * Fixed bug with extracting files if the DMAV section was larger than the
      audio file.
* 1.1
    * Added support for extracting DMAV sections of voice audio banks.
    * bnk_pc_extractor now uses a default log file location if none is
      supplied.
* 1.0
    * Initial release.
