# Problem Template Generator - Setup Guide

## Overview

The `generate_problem_template.py` script automates the creation of DSA problem directories with auto-filled content using Google's Gemini Flash API.

## Prerequisites

### 1. Get a Gemini API Key

- Go to [Google AI Studio](https://aistudio.google.com/app/apikey)
- Sign in with your Google account
- Click "Create API Key"
- Copy the API key

### 2. Install Dependencies

```bash
cd scripts
pip install -r requirements.txt
```

### 3. Set Environment Variable

#### On Windows (PowerShell):
```powershell
$env:GEMINI_API_KEY="your-api-key-here"
```

#### On Windows (Command Prompt):
```cmd
set GEMINI_API_KEY=your-api-key-here
```

#### On Windows (Permanent - Add to System Environment Variables):
1. Press `Win + X` and select "System"
2. Click "Advanced system settings"
3. Click "Environment Variables"
4. Click "New" under "User variables"
5. Variable name: `GEMINI_API_KEY`
6. Variable value: `your-api-key-here`
7. Click "OK" and restart your terminal

#### On macOS/Linux:
```bash
export GEMINI_API_KEY="your-api-key-here"
```

For persistent setup, add to `~/.bashrc` or `~/.zshrc`:
```bash
echo 'export GEMINI_API_KEY="your-api-key-here"' >> ~/.bashrc
source ~/.bashrc
```

## Usage

### Basic Run

```bash
python generate_problem_template.py
```

The script will prompt you for:
1. **Topic**: Category of the problem (e.g., array, string, tree, graph, linked-list, etc.)
2. **Difficulty**: Easy, Medium, or Hard
3. **Problem URL**: Link to the problem (e.g., LeetCode URL)

### Example Workflow

```bash
$ python generate_problem_template.py

============================================================
DSA Problem Template Generator
============================================================

Enter topic (e.g., array, string, tree, graph): array
Enter difficulty (Easy/Medium/Hard): Medium
Enter problem URL (e.g., https://leetcode.com/problems/...): https://leetcode.com/problems/two-sum/

Analyzing problem with Gemini...

============================================================
✓ Problem template created successfully!
============================================================
Problem: Two Sum
Difficulty: Medium
Topic: array
Location: problems/array/medium/two sum

Generated files:
  - problems/array/medium/two sum/README.md
  - problems/array/medium/two sum/metadata.json

Next steps:
  1. Review and edit the generated files
  2. Add your solution to README.md
  3. Fill in intuition and takeaways
============================================================
```

## Features

✅ **Auto-fills content using Gemini AI:**
- Problem title
- Platform (LeetCode, GeeksForGeeks, etc.)
- Problem description
- Topics and patterns
- Constraints
- Examples
- Expected time/space complexity
- Companies that ask this problem

✅ **Creates organized folder structure:**
```
problems/
└── topic/
    └── difficulty/
        └── problem-name/
            ├── README.md
            └── metadata.json
```

✅ **Generates two template files:**
- `README.md` - Structured problem documentation
- `metadata.json` - Problem metadata and tracking information

✅ **Futureproof design:**
- Uses Gemini 2.0 Flash (latest model)
- Proper error handling
- Secure API key management
- Extensible class-based architecture
- Handles multiple platforms

## What Gets Auto-filled

### README.md
- Problem title
- Difficulty level
- Topics
- Platform name
- Problem link
- Full problem description
- Examples (input/output)
- Constraints
- Template sections for:
  - Intuition
  - Solution
  - Takeaways
  - C++ Concepts

### metadata.json
- Unique problem ID
- Title
- Platform
- Difficulty
- Topics
- Problem link
- Time complexity estimate
- Space complexity estimate
- Today's date as solved_date
- Companies (auto-detected from platform)
- Patterns (auto-detected)
- Placeholder for revision_count and takeaways

## Troubleshooting

### Issue: "GEMINI_API_KEY environment variable not set"
**Solution:** Make sure you've set the environment variable correctly. Test it:

```bash
# On Windows (PowerShell)
echo $env:GEMINI_API_KEY

# On macOS/Linux
echo $GEMINI_API_KEY
```

### Issue: "Could not fetch HTML from URL"
**Solution:** This is just a warning. The script can still work with Gemini analyzing the URL directly. Make sure your internet connection is stable.

### Issue: "Could not parse JSON from response"
**Solution:** The API might have returned an unexpected format. Try again - it could be a temporary issue. Check that your API key is valid.

### Issue: "Folder already exists"
**Solution:** The script will create the folder if it doesn't exist. If it already exists, files will be overwritten. To keep both, manually rename one of them.

## Tips

1. **Review Generated Content**: Always review the auto-generated content. Gemini does its best but may need manual corrections.

2. **URL Formats**: Works best with:
   - LeetCode: `https://leetcode.com/problems/problem-slug/`
   - GeeksForGeeks: `https://www.geeksforgeeks.org/problem-page/`
   - Direct problem pages with visible problem statements

3. **Custom Metadata**: After generation, you can manually edit:
   - `solution_link` - Add link to your solution
   - `companies` - Refine the list
   - `patterns` - Add or remove patterns
   - `takeaways` - Add learning points after solving

4. **Batch Creation**: You can run the script multiple times in sequence to create multiple problems.

## Advanced Customization

To modify the script's behavior:

1. **Change AI Model**: In `__init__` method, change:
   ```python
   self.model = genai.GenerativeModel("gemini-2.0-flash")
   ```

2. **Adjust Prompts**: Edit the `extract_problem_details` method to customize what information is extracted.

3. **Change Folder Structure**: Modify the `create_folder_structure` method to organize problems differently.

## License & Notes

This script is part of your personal DSA tracker repository. It uses Google's Gemini API for content generation.

---

**Last Updated:** May 2026
