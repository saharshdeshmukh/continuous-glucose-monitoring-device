# Continuous Glucose Monitoring Device (Starter)

This is a beginner-friendly starter repository scaffold for the **Continuous Glucose Monitoring Device** project.
It includes a simple firmware skeleton, a Python processing stub, a .gitignore, a sample BOM, and helpful instructions.

> IMPORTANT: This project is a **student project/demo** and **not** a medical device. Do NOT use for real medical diagnosis.

## What is included
- `firmware/main.ino` — ESP32/Arduino skeleton with comments.
- `processing/analyze_stream.py` — small Python stub that demonstrates the glucose formula.
- `processing/requirements.txt` — Python dependencies list.
- `.gitignore` — ignores build files, virtualenvs, and sensitive files.
- `hardware/bom.csv` — sample Bill of Materials.
- `docs/README.md` — where to add images/screenshots.
- `firebase_config.example.json` — placeholder (do NOT commit real keys).

## Quick steps (simplest)
1. Download and unzip this starter folder.
2. Create a new GitHub repo named `continuous-glucose-monitoring-device` (or your chosen name).
3. Clone the GitHub repo to your machine.
4. Copy the files from this starter folder into the cloned repo folder.
5. In the cloned folder run:
   ```
   git add .
   git commit -m "Initial commit: starter project"
   git push
   ```
6. Your files will be visible on GitHub.

If you prefer to start locally and then create the GitHub repo, follow the commands in the "Commands" section below.

---

## Commands (step-by-step)
See the top-level `COMMANDS.md` included in this starter for the exact command sequence with explanations for both **Option A (create GitHub repo first)** and **Option B (init locally first)**.

--- 
Happy coding! If you want, after this you can edit `firmware/main.ino` with your real code and `processing/analyze_stream.py` with your real data processing.
