param(
  [string]$Configuration = 'Debug',
  [string]$Generator = 'MinGW Makefiles',
  [int]$Jobs = 4
)

$ScriptDir = Split-Path -Parent $MyInvocation.MyCommand.Definition
$ProjectRoot = Resolve-Path (Join-Path $ScriptDir '..\..')
$BuildDir = Join-Path $ProjectRoot 'build'
if(-not (Test-Path $BuildDir)) { New-Item -ItemType Directory -Path $BuildDir | Out-Null }
cmake -S $ProjectRoot -B $BuildDir -G $Generator -DCMAKE_BUILD_TYPE=$Configuration
cmake --build $BuildDir -- -j $Jobs
Write-Host "Built ($Configuration) -> $($ProjectRoot)\bin\practica.exe"