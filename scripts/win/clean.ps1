$ScriptDir = Split-Path -Parent $MyInvocation.MyCommand.Definition
$ProjectRoot = Resolve-Path (Join-Path $ScriptDir '..\..')

Remove-Item -Recurse -Force (Join-Path $ProjectRoot 'build'), (Join-Path $ProjectRoot 'bin'), (Join-Path $ProjectRoot 'lib') -ErrorAction SilentlyContinue
Remove-Item -Force (Join-Path $ProjectRoot 'CMakeCache.txt') -ErrorAction SilentlyContinue
Remove-Item -Recurse -Force (Join-Path $ProjectRoot 'CMakeFiles') -ErrorAction SilentlyContinue
Write-Host "Cleaned build/, bin/, lib/ in $ProjectRoot"