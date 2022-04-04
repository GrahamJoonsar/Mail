@echo off
echo Build Start
gcc src/language.c src/file_operations.c src/direction.c -o build/mail
echo Build Complete