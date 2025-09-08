# COMMANDS.md

This file shows step-by-step commands for two simple ways to get your starter files onto GitHub.

--- Option A: Create GitHub repo first (recommended)
1. On GitHub website, create a new repository named: continuous-glucose-monitoring-device
   - Do NOT initialize with README (you will copy local files into it)
2. Clone the new (empty) repo to your PC:
   git clone https://github.com/<your-username>/continuous-glucose-monitoring-device.git
3. Copy the files from the starter folder into the cloned repo folder (use file explorer or terminal)
4. In the cloned folder:
   git add .
   git commit -m "Initial commit: add starter project files"
   git push

--- Option B: Start locally and push to GitHub
1. On your PC unzip the starter folder.
2. Inside the starter folder run:
   git init
   git branch -M main
   git remote add origin https://github.com/<your-username>/continuous-glucose-monitoring-device.git
   git add .
   git commit -m "Initial commit: add starter project files"
   git push -u origin main

Notes:
- Replace <your-username> with your GitHub username.
- If Git asks for username/password when pushing, use GitHub credentials (or better: set up SSH keys or use GitHub CLI / GitHub Desktop).
