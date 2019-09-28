@echo off

echo test_%2



%1 in_%2.txt <in_%2.txt >output_%2.txt



fc out_%2.txt output_%2.txt

if %errorlevel%==0 (echo test passed)

if %errorlevel%==1 (echo test failed)



DEL output_%2.txt

pause
