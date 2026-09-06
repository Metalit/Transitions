#!/usr/bin/env pwsh

Param(
    [Parameter(Mandatory=$false)]
    [Switch] $clean,

    [Parameter(Mandatory=$false)]
    [ValidateSet("Debug", "Release", "RelWithDebInfo", "MinSizeRel")]
    [String] $buildType="RelWithDebInfo",

    [Parameter(Mandatory=$false)]
    [Switch] $help
)

if ($help -eq $true) {
    Write-Output "`"Build`" - Copiles your mod into a `".so`" or a `".a`" library"
    Write-Output "`n-- Arguments --`n"

    Write-Output "-Clean `t`t Deletes the `"build`" folder, so that the entire library is rebuilt"
    Write-Output "-BuildType `t Selects Debug, Release, RelWithDebInfo, or MinSizeRel (default: RelWithDebInfo)"

    exit
}

# if user specified clean, remove all build files
if ($clean.IsPresent) {
    if (Test-Path -Path "build") {
        Remove-Item -LiteralPath "build" -Recurse -Force -ErrorAction Stop
    }
}


if (($clean.IsPresent) -or (-not (Test-Path -Path "build"))) {
    New-Item -Path build -ItemType Directory
}

Write-Output "Configuring CMake build type: $buildType"
& cmake -G "Ninja" "-DCMAKE_BUILD_TYPE=$buildType" -B build
if ($LASTEXITCODE -ne 0) {
    exit $LASTEXITCODE
}
& cmake --build ./build
