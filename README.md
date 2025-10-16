# Instagram Follower Analyzer

This tool helps you identify Instagram accounts that **don’t follow you back** and accounts that **you don’t follow back**.  

## Features
- See which users you follow who aren’t following you back.
- See which users follow you that you don’t follow back.
- Open users’ profiles directly in your browser from the app. (If you choose the GUI version)

---

## Getting Started

### I. Download Your Personal Data from Meta

1. Go to [Instagram Account Center](https://accountscenter.instagram.com/info_and_permissions) and select **Export your information**.  
2. Select the account you want to analyze and click **Export to device**.  
3. Customize the export by clicking **Customize information**:  
   - Uncheck everything except **Followers and following** under the **Connections** tab to speed up the download.  
4. Set the date range to **All time**.  
5. Choose **JSON format** and click **Start export**.  
   - You will need to enter your password to confirm.  
   - Instagram will email you when the download is ready (usually ~10 minutes).  
6. Unzip the downloaded archive. Locate the files for your connections, usually named `following.json` and `followers.json`.  
   - If the names are different, rename them to `following.json` and `followers.json`.

---

### II. Download the Tool

Download the `.exe` file from the [releases section](#).
| Version                             | Platform                  | Interface    | Description                                       |
| ----------------------------------- | ------------------------- | ------------ | ------------------------------------------------- |
| 🪟 **Windows GUI**                  | Windows 10/11             | Graphical    | Easy to use, shows results in interactive windows |
| 🍎 **macOS GUI**                    | macOS 12+                 | Graphical    | Same interface as Windows, optimized for macOS    |
| 🧑‍💻 **No GUI (Linux / Terminal)** | Any (Windows/macOS/Linux) | Command-line | Runs in terminal, simple text output              |

Choose the version that matches your operating system.
If unsure, use the No GUI version — it works everywhere.

---

### III. Run the Tool

# For Windows GUI / Mac OS GUI
1. Place the `following.json` and `followers.json` files in the same directory as the `.exe` file.  
2. Double-click the `.exe` to run it.  

# For No GUI (Terminal)
1. Place followers.json and following.json in the same folder as the executable.
2. Open a terminal in that folder.
3. Run:
```bash
./InstaCheckerNoGUI
```
---

### IV. Using the Tool

- Two windows will appear:  
  1. **Don’t follow you back** – shows accounts you follow who don’t follow you back.  
  2. **You don’t follow back** – shows accounts following you that you don’t follow.  
- Click on any username in the list to open their Instagram profile in your browser.

---

### Notes
- Make sure your JSON files are named correctly and placed in the same folder as the `.exe`.  
- This tool only reads your exported Instagram data; it does not interact with Instagram directly.  