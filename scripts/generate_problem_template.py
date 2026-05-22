#!/usr/bin/env python3
"""
DSA Problem Template Generator

This script automates the creation of problem directories with README.md and metadata.json
files by using the Gemini Flash API to extract problem details from URLs.

Features:
- Fetches problem details from URLs using Gemini
- Auto-fills README and metadata templates
- Creates proper folder structures
- Supports multiple problem platforms
- Secure API key management via environment variables
"""

import os
import json
import sys
from pathlib import Path
from datetime import datetime
from typing import Optional, Dict, Any
import requests
import re
from urllib.parse import urlparse

import google.generativeai as genai


class ProblemTemplateGenerator:
    """Generator for DSA problem templates using Gemini AI."""

    def __init__(self):
        """Initialize the generator with Gemini configuration."""
        self.api_key = os.getenv("GEMINI_API_KEY") or "AIzaSyCjQ8FpmsFuBbpJGxOZObW-MEp3AjQ0q8s"
        if not self.api_key:
            raise ValueError(
                "GEMINI_API_KEY environment variable not set. "
                "Please set it before running this script."
            )

        genai.configure(api_key=self.api_key)
        self.model = genai.GenerativeModel("gemini-2.5-flash")
        self.base_path = Path(__file__).parent.parent / "problems"

    def get_user_inputs(self) -> Dict[str, str]:
        """Get user inputs for topic, difficulty, and problem URL."""
        print("\n" + "=" * 60)
        print("DSA Problem Template Generator")
        print("=" * 60 + "\n")

        topic = input("Enter topic (e.g., array, string, tree, graph): ").strip()
        if not topic:
            raise ValueError("Topic cannot be empty")

        difficulty = input(
            "Enter difficulty (Easy/Medium/Hard): "
        ).strip()
        if difficulty not in ["Easy", "Medium", "Hard"]:
            raise ValueError("Difficulty must be Easy, Medium, or Hard")

        url = input("Enter problem URL (e.g., https://leetcode.com/problems/...): ").strip()
        if not url:
            raise ValueError("URL cannot be empty")

        return {"topic": topic.lower(), "difficulty": difficulty, "url": url}

    def fetch_problem_html(self, url: str) -> Optional[str]:
        """Fetch HTML content from the problem URL."""
        try:
            headers = {
                "User-Agent": "Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36"
            }
            response = requests.get(url, headers=headers, timeout=10)
            response.raise_for_status()
            return response.text
        except Exception as e:
            print(f"Warning: Could not fetch HTML from URL: {e}")
            return None

    def extract_problem_details(
        self, url: str, html_content: Optional[str] = None
    ) -> Dict[str, Any]:
        """Use Gemini to extract problem details from URL and HTML content."""
        print("\nAnalyzing problem with Gemini...")

        html_context = ""
        if html_content:
            # Limit HTML to first 8000 chars to avoid token limits
            html_context = f"\n\nHTML Content (first part):\n{html_content[:8000]}"

        prompt = f"""
Analyze the following problem URL and extract detailed information about the coding problem.

URL: {url}
{html_context}

Please extract and provide the following information in JSON format:
{{
    "title": "Problem title as appears on the platform",
    "platform": "Platform name (e.g., LeetCode, GeeksForGeeks, NeetCode)",
    "description": "Complete problem statement/description (2-3 sentences)",
    "topics": ["main topic 1", "main topic 2"],
    "time_complexity": "Expected time complexity (e.g., O(n), O(n log n))",
    "space_complexity": "Expected space complexity (e.g., O(1), O(n))",
    "constraints": ["constraint 1", "constraint 2", "constraint 3"],
    "examples": [
        {{
            "input": "Input description",
            "output": "Output description",
            "explanation": "Brief explanation"
        }}
    ],
    "companies": ["Company 1", "Company 2"],
    "patterns": ["Pattern 1", "Pattern 2"]
}}

Only return valid JSON. If you cannot find certain information, omit the field or provide best guess based on problem type.
If there are no examples visible, return empty array for examples.
"""

        try:
            response = self.model.generate_content(prompt)
            response_text = response.text

            # Extract JSON from response
            json_match = re.search(r"\{.*\}", response_text, re.DOTALL)
            if json_match:
                problem_data = json.loads(json_match.group())
                return problem_data
            else:
                raise ValueError("Could not parse JSON from response")
        except Exception as e:
            print(f"Error analyzing problem with Gemini: {e}")
            return {}

    def create_folder_structure(self, topic: str, difficulty: str, problem_name: str) -> Path:
        """Create the folder structure for the problem."""
        problem_path = (
            self.base_path / topic / difficulty.lower() / problem_name
        )
        problem_path.mkdir(parents=True, exist_ok=True)
        return problem_path

    def format_readme(
        self, problem_data: Dict[str, Any], url: str, problem_name: str
    ) -> str:
        """Format the README.md content from problem data."""
        title = problem_data.get("title", problem_name)
        platform = problem_data.get("platform", "Unknown")
        description = problem_data.get("description", "Add problem description here.")
        topics = ", ".join(problem_data.get("topics", []))
        constraints = problem_data.get("constraints", [])
        examples = problem_data.get("examples", [])

        # Build examples section
        examples_section = ""
        for i, example in enumerate(examples, 1):
            examples_section += f"""### Example {i}

```txt
Input: {example.get('input', '')}

Output: {example.get('output', '')}
```
"""
            if example.get("explanation"):
                examples_section += f"\nExplanation: {example.get('explanation')}\n\n"

        # Default examples if none found
        if not examples_section:
            examples_section = "### Example 1\n\n```txt\nInput: \n\nOutput: \n```\n\n"

        # Build constraints section
        constraints_section = ""
        for constraint in constraints:
            constraints_section += f"- `{constraint}`\n"

        # Default constraints if none found
        if not constraints_section:
            constraints_section = "- `1 <= a <= x`\n- `0 <= b <= y`\n"

        readme_content = f"""# {title}

- Difficulty: Medium
- Topic: {topics}
- Platform: {platform}
- Link: {url}

---

## Problem Statement

{description}

---

## Examples

{examples_section}---

## Constraints

{constraints_section}---

## Intuition

[Add your approach here]

---

## Solution

[Add your solution here]

---

## Takeaways

- takeaway1
- takeaway2

## C++ Concepts

- 
"""
        return readme_content

    def format_metadata(
        self,
        problem_data: Dict[str, Any],
        url: str,
        difficulty: str,
        topic: str,
        problem_id: int,
    ) -> Dict[str, Any]:
        """Format the metadata.json content from problem data."""
        metadata = {
            "id": problem_id,
            "title": problem_data.get("title", ""),
            "platform": problem_data.get("platform", "Unknown"),
            "difficulty": difficulty,
            "topics": problem_data.get("topics", [topic]),
            "problem_link": url,
            "solution_link": "",
            "time_complexity": problem_data.get("time_complexity", ""),
            "space_complexity": problem_data.get("space_complexity", ""),
            "revision_count": 0,
            "solved_date": datetime.now().strftime("%Y-%m-%d"),
            "companies": problem_data.get("companies", []),
            "patterns": problem_data.get("patterns", []),
            "takeaways": []
        }
        return metadata

    def get_next_problem_id(self) -> int:
        """Get the next available problem ID."""
        # Count problem folders under problems/<topic>/<difficulty>/<problem-name>
        count = 0
        if not self.base_path.exists():
            return 1

        try:
            for topic_dir in self.base_path.iterdir():
                if not topic_dir.is_dir():
                    continue
                for diff_dir in topic_dir.iterdir():
                    if not diff_dir.is_dir():
                        continue
                    for problem_dir in diff_dir.iterdir():
                        if problem_dir.is_dir():
                            count += 1
        except Exception:
            # Fallback: count existing metadata.json files if directory traversal fails
            count = 0
            for metadata_file in self.base_path.rglob("metadata.json"):
                try:
                    with open(metadata_file) as f:
                        data = json.load(f)
                        if data.get("id"):
                            count += 1
                except Exception:
                    pass

        return count + 1

    def sanitize_folder_name(self, name: str) -> str:
        """Sanitize folder name to be filesystem-safe."""
        # Remove special characters and replace spaces with underscores
        name = re.sub(r'[^\w\s-]', '', name)
        name = re.sub(r'[\s_]+', ' ', name)
        # Remove leading numbers
        name = re.sub(r'^\d+', '', name)
        return name.strip()

    def run(self):
        """Main execution flow."""
        try:
            # Get user inputs
            inputs = self.get_user_inputs()
            topic = inputs["topic"]
            difficulty = inputs["difficulty"]
            url = inputs["url"]

            # Fetch problem HTML
            html_content = self.fetch_problem_html(url)

            # Extract problem details
            problem_data = self.extract_problem_details(url, html_content)

            if not problem_data:
                print("Warning: Could not extract problem details. Using minimal data.")
                problem_data = {"title": "New Problem", "platform": "Unknown"}

            # Generate folder name
            title = problem_data.get("title", "problem")
            problem_folder_name = self.sanitize_folder_name(title)

            # Create folder structure
            problem_path = self.create_folder_structure(
                topic, difficulty, problem_folder_name
            )

            # Get next ID
            problem_id = self.get_next_problem_id()

            # Format README
            readme_content = self.format_readme(problem_data, url, problem_folder_name)

            # Format metadata
            metadata = self.format_metadata(
                problem_data, url, difficulty, topic, problem_id
            )

            # Write README
            readme_path = problem_path / "README.md"
            with open(readme_path, "w", encoding="utf-8") as f:
                f.write(readme_content)

            # Write metadata
            metadata_path = problem_path / "metadata.json"
            with open(metadata_path, "w", encoding="utf-8") as f:
                json.dump(metadata, f, indent=2)

            # Success message
            print("\n" + "=" * 60)
            print("✓ Problem template created successfully!")
            print("=" * 60)
            print(f"Problem: {problem_data.get('title', 'Unknown')}")
            print(f"Difficulty: {difficulty}")
            print(f"Topic: {topic}")
            print(f"Location: {problem_path}")
            print("\nGenerated files:")
            print(f"  - {readme_path}")
            print(f"  - {metadata_path}")
            print("\nNext steps:")
            print("  1. Review and edit the generated files")
            print("  2. Add your solution to README.md")
            print("  3. Fill in intuition and takeaways")
            print("=" * 60 + "\n")

        except KeyboardInterrupt:
            print("\n\nOperation cancelled by user.")
            sys.exit(0)
        except Exception as e:
            print(f"\n✗ Error: {e}")
            sys.exit(1)


def main():
    """Entry point for the script."""
    generator = ProblemTemplateGenerator()
    generator.run()


if __name__ == "__main__":
    main()
