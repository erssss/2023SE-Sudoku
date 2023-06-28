@REM @echo ********************* START TEST *********************

@REM set CPPLINT="G:/users/L/AppData/Local/Programs/Python/envs/myenv/myenv/Scripts/cpplint.exe"
@REM set INCLUDE_DIR="G:/repo/2023SE-sudoku/include"
@REM set SOURCE_DIR="G:/repo/2023SE-sudoku/src"

@REM for /R %INCLUDE_DIR% %%G in (*.cpp, *.h) do (
@REM     @echo --------- Checking: %%G ---------
@REM     %CPPLINT% %%G
@REM )
@REM for /R %SOURCE_DIR% %%G in (*.cpp, *.h) do (
@REM     @echo --------- Checking: %%G ---------
@REM     %CPPLINT% %%G
@REM )

@echo ********************* END TEST *********************


echo ********************* START TEST ********************* >> %OUTPUT_FILE%

set CPPLINT="G:/users/L/AppData/Local/Programs/Python/envs/myenv/myenv/Scripts/cpplint.exe"
set INCLUDE_DIR="G:/repo/2023SE-sudoku/include"
set SOURCE_DIR="G:/repo/2023SE-sudoku/src"
set OUTPUT_FILE=lint_result.txt

for /R %INCLUDE_DIR% %%G in (*.cpp, *.h) do (
    echo --------- Checking: %%G --------- >> %OUTPUT_FILE%
    %CPPLINT% %%G >> %OUTPUT_FILE%
)
for /R %SOURCE_DIR% %%G in (*.cpp, *.h) do (
    echo --------- Checking: %%G --------- >> %OUTPUT_FILE%
    %CPPLINT% %%G >> %OUTPUT_FILE%
)
echo ********************* END TEST ********************* >> %OUTPUT_FILE%

type %OUTPUT_FILE%
@REM del %OUTPUT_FILE%