# File creates a tag and pushes it to the remote repository
# Script to release a new version of the mod to github easily, 
# you need to cherry-pick the commits to the branches first manually though

# Get version from cli argument
$modVersion = $args[0]

# Check if the input is empty
if ($modVersion -eq "") {
    Write-Host "No version given! (example: 0.2.12)"
    exit
}

# Check if version is in format x.x.x and has no other characters 
if ($modVersion -notmatch '^\d+\.\d+\.\d+$') {
    Write-Host "Version is not in format x.x.x (example: 0.2.12) or have other characters! it's the first argument"
    exit
}

# Print version
Write-Host "Gonna do version: $modVersion"


# Create new tags array
$new_tags = @()

Write-Host "New tag name is: v$modVersion"

  
# Ask if we should continue
Write-Host "Continue? (y/n)"
$continue = Read-Host

# If not then exit
if ($continue -ne "y") {
    exit
}

Write-Host "Fetching tags from remote..."
# Fetch tags from remote
git fetch --tags
Write-Host "Done!"

$tag = "v$modVersion"

# Check if the tag already exists, if it does then skip it
$tagExists = git tag | Select-String -Pattern $tag
if ($tagExists) {
    Write-Host "Tag $tag already exists! skipping..."
    continue
}

# Get the current branch
$branch = git branch --show-current

Write-Host "Created tag: $tag from branch: $branch for $version" 
# Create tag
git tag $tag $branch -m "Release $modVersion for Beat Saber $version"



# Ask if we should push
Write-Host "Push tags? (y/n)"
$push = Read-Host

# If not then exit
if ($push -ne "y") {
    exit
}

# Push tag 
Write-Host "Pushing $tag"
# Push tag
git push origin $tag

Write-Host "Done! the tag is pushed! Yaay! 🎉"