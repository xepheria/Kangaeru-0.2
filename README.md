# Kangaeru-0.2
Now working with Cocos2d-x 3.4

Kangaeru - Learning Kanji Application!

Installation instructions
--------------------------------------------------------------------

Cocos is a pain in batooskie, so the easiest way I've found to do this is the following:

1. Use terminal and create a new cocos project using the following command.
   cocos new Kangaeru -p edu.Kangaeru.Kangaeru -l cpp -d ~/Kangaeru
   
2. Open up your new project directory. Should be under your root directory, in the folder Kangaeru.
   
3. Download the zip from the github repository (if you don't already have it).

4. Delete everything in the folder Kangaeru/Classes (the one you just created) and replace it was the contents of Kangaeru/Classes from the zip you downloaded.

5. Do the same thing with the folder Kangaeru/Resources.

6. You should be able to just replace the CMakeLists.txt file.

7. If you're running linux, great...just go to root and do the cocos run -p linux command and you're golden. If you want to do android tests, continue...

8. Go to your local proj.android/jni and replace the Android.mk file with the one found in the zip you downloaded.

9. Run "./build_native.py -p -19" from the proj.android directory in terminal. Navigate to the bin folder and run "adb install Kangaeru-debug.apk". If your android is plugged in with debugging mode enabled, it should install to your device. If you modify code and need to reinstall it, UNINSTALL it from the device first or it won't work.

10. If you're just testing on linux and android, hurray! If you're working on a mac or windows, it sucks to be you, because I don't know how to work those yet. Your options are virtual box or something equally crafty. Or you could figure out how to work it on your machine.

FAQS
--------------------------------------------------------------------

Q: How do I run Kangaeru on my Mac/Windows/iPhone/microwave oven?

A: I don't know. See #10 above.


Q: Such and such doesn't work! What do I do?

A: Report the bug on github please.


Q: Your installation guide sucks! It doesn't work!

A: Three possibilities: You did it wrong, your machine is a piece of poop, or I legitimately missed something. Report the bug on github if you find it to be the third option.

CREDITS
--------------------------------------------------------------------

Alex
Sophia
Maria
Mariah
Steven
Dylan

Kishimoto先生
