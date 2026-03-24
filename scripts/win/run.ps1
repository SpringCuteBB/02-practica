param(
  [Parameter(ValueFromRemainingArguments=$true)]
  $Args
)
$ScriptDir = Split-Path -Parent $MyInvocation.MyCommand.Definition
$ProjectRoot = Resolve-Path (Join-Path $ScriptDir '..\..')
$exe = Join-Path -Path $ProjectRoot -ChildPath 'bin\practica.exe'
if(-not (Test-Path $exe)) { Write-Error "Executable not found: $exe"; exit 1 }
Push-Location $ProjectRoot
& $exe @Args
Pop-Location