#!/usr/bin/env python3
"""
DSA Problem Template Generator

This script automates the creation of problem directories with README.md and metadata.json
files by using the Gemini API to extract problem details from URLs.

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
from typing import Optional, Dict, Any, List, Tuple
import re
from dotenv import load_dotenv

import google.generativeai as genai

load_dotenv()


# Unified deduped topic list from NeetCode 150/250 + Striver A2Z sheets.
# Each entry is (display_name, folder_slug).
TOPICS: List[Tuple[str, str]] = [
    ("Arrays & Hashing", "arrays-hashing"),
    ("Two Pointers", "two-pointers"),
    ("Sliding Window", "sliding-window"),
    ("Stack", "stack"),
    ("Queue", "queue"),
    ("Binary Search", "binary-search"),
    ("Linked List", "linked-list"),
    ("Trees", "trees"),
    ("Binary Search Trees", "binary-search-trees"),
    ("Tries", "tries"),
    ("Heap / Priority Queue", "heap-priority-queue"),
    ("Backtracking", "backtracking"),
    ("Recursion", "recursion"),
    ("Graphs", "graphs"),
    ("Advanced Graphs", "advanced-graphs"),
    ("1-D Dynamic Programming", "1d-dynamic-programming"),
    ("2-D Dynamic Programming", "2d-dynamic-programming"),
    ("Greedy", "greedy"),
    ("Intervals", "intervals"),
    ("Math & Geometry", "math-geometry"),
    ("Bit Manipulation", "bit-manipulation"),
    ("Strings", "strings"),
    ("Sorting", "sorting"),
]

DIFFICULTY_MAP = {"E": "Easy", "M": "Medium", "H": "Hard"}


class ProblemTemplateGenerator:
    """Generator for DSA problem templates using Gemini AI."""

    def __init__(self):
        """Initialize the generator with Gemini configuration."""
        self.api_key = os.getenv("GEMINI_API_KEY")
        print("API key: ", self.api_key)
        if not self.api_key:
            raise ValueError(
                "GEMINI_API_KEY environment variable not set. "
                "Please set it before running this script."
            )

        model_name = os.getenv("GEMINI_MODEL", "gemini-3.6-flash")
        genai.configure(api_key=self.api_key)
        self.model = genai.GenerativeModel(model_name)
        self.base_path = Path(__file__).parent.parent / "problems"

    def _resolve_topic(self, raw: str) -> Tuple[str, str]:
        """Resolve user input to a (display_name, slug) topic.

        Accepts a 1-based number, a prefix of the display name, or the full
        display name. Matching is case-insensitive. Raises ValueError on
        no-match or ambiguous prefix.
        """
        raw = raw.strip()
        if not raw:
            raise ValueError("Topic cannot be empty")

        if raw.isdigit():
            idx = int(raw)
            if not 1 <= idx <= len(TOPICS):
                raise ValueError(f"Topic number must be 1-{len(TOPICS)}")
            return TOPICS[idx - 1]

        needle = raw.lower()
        matches = [t for t in TOPICS if t[0].lower().startswith(needle)]
        if len(matches) == 1:
            return matches[0]
        if len(matches) > 1:
            names = ", ".join(m[0] for m in matches)
            raise ValueError(f"Ambiguous topic '{raw}'. Matches: {names}")
        raise ValueError(f"No topic matched '{raw}'")

    def _resolve_difficulty(self, raw: str) -> str:
        """Resolve E/M/H (any case) to full difficulty name."""
        raw = raw.strip().upper()
        if raw not in DIFFICULTY_MAP:
            raise ValueError("Difficulty must be E, M, or H")
        return DIFFICULTY_MAP[raw]

    def get_user_inputs(self) -> Dict[str, str]:
        """Get user inputs for topic, difficulty, and problem URL."""
        print("\n" + "=" * 60)
        print("DSA Problem Template Generator")
        print("=" * 60 + "\n")

        print("Topics (NeetCode + Striver):")
        for i, (name, _) in enumerate(TOPICS, 1):
            print(f"  {i:>2}. {name}")
        print()

        topic_display, topic_slug = self._resolve_topic(
            input("Enter topic (number, prefix, or full name): ")
        )

        difficulty = self._resolve_difficulty(
            input("Enter difficulty (E/M/H): ")
        )

        url = input("Enter problem URL (e.g., https://leetcode.com/problems/...): ").strip()
        if not url:
            raise ValueError("URL cannot be empty")

        return {
            "topic_display": topic_display,
            "topic_slug": topic_slug,
            "difficulty": difficulty,
            "url": url,
        }

    def extract_problem_details(self, url: str) -> Optional[Dict[str, Any]]:
        """Use Gemini to extract problem details from URL.

        Returns the parsed problem data on success, or None if the Gemini
        call fails for any reason (invalid key, network, parse error, etc.).
        """
        print("\nAnalyzing problem with Gemini...")

        prompt = f"""
Analyze the following problem URL and extract detailed information about the coding problem.

URL: {url}

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
    "patterns": ["Pattern 1", "Pattern 2"],
    "intuition": "A short 2-4 sentence intuition explaining the core idea / approach for solving this problem. Plain prose, no code.",
    "takeaways": ["short takeaway 1", "short takeaway 2", "short takeaway 3"]
}}

Only return valid JSON. If you cannot find certain information, omit the field or provide best guess based on problem type.
If there are no examples visible, return empty array for examples.
Always include "intuition" and "takeaways" based on your own understanding of the problem if the URL content is unavailable.
"""

        try:
            response = self.model.generate_content(prompt)
            response_text = response.text

            json_match = re.search(r"\{.*\}", response_text, re.DOTALL)
            if not json_match:
                raise ValueError("Could not parse JSON from response")
            return json.loads(json_match.group())
        except Exception as e:
            print(f"Gemini call failed: {e}")
            return None

    def create_folder_structure(self, topic_slug: str, difficulty: str, problem_name: str) -> Path:
        """Create the folder structure for the problem."""
        problem_path = (
            self.base_path / topic_slug / difficulty.lower() / problem_name
        )
        problem_path.mkdir(parents=True, exist_ok=True)
        return problem_path

    def format_readme(
        self,
        problem_data: Dict[str, Any],
        url: str,
        problem_name: str,
        difficulty: str,
    ) -> str:
        """Format the README.md content from problem data."""
        title = problem_data.get("title", problem_name)
        platform = problem_data.get("platform", "Unknown")
        description = problem_data.get("description", "Add problem description here.")
        topics = ", ".join(problem_data.get("topics", []))
        constraints = problem_data.get("constraints", [])
        examples = problem_data.get("examples", [])
        intuition = problem_data.get("intuition", "").strip() or "[Add your approach here]"
        takeaways = problem_data.get("takeaways", []) or ["takeaway1", "takeaway2"]
        takeaways_section = "".join(f"- {t}\n" for t in takeaways)

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

        if not examples_section:
            examples_section = "### Example 1\n\n```txt\nInput: \n\nOutput: \n```\n\n"

        constraints_section = ""
        for constraint in constraints:
            constraints_section += f"- `{constraint}`\n"

        if not constraints_section:
            constraints_section = "- `1 <= a <= x`\n- `0 <= b <= y`\n"

        readme_content = f"""# {title}

- Difficulty: {difficulty}
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

{intuition}

---

## Takeaways

{takeaways_section}
## C++ Concepts

-
"""
        return readme_content

    def format_metadata(
        self,
        problem_data: Dict[str, Any],
        url: str,
        difficulty: str,
        topic_display: str,
        problem_id: int,
    ) -> Dict[str, Any]:
        """Format the metadata.json content from problem data."""
        metadata = {
            "id": problem_id,
            "title": problem_data.get("title", ""),
            "platform": problem_data.get("platform", "Unknown"),
            "difficulty": difficulty,
            "topics": problem_data.get("topics", [topic_display]),
            "problem_link": url,
            "solution_link": "",
            "time_complexity": problem_data.get("time_complexity", ""),
            "space_complexity": problem_data.get("space_complexity", ""),
            "revision_count": 0,
            "solved_date": datetime.now().strftime("%Y-%m-%d"),
            "companies": problem_data.get("companies", []),
            "patterns": problem_data.get("patterns", []),
            "takeaways": problem_data.get("takeaways", [])
        }
        return metadata

    def get_next_problem_id(self) -> int:
        """Get the next available problem ID."""
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
        name = re.sub(r'[^\w\s-]', '', name)
        name = re.sub(r'[\s_]+', ' ', name)
        name = re.sub(r'^\d+', '', name)
        return name.strip()

    def _prompt_yes_no(self, question: str) -> bool:
        ans = input(f"{question} (y/n): ").strip().lower()
        return ans in ("y", "yes")

    def run(self):
        """Main execution flow."""
        try:
            inputs = self.get_user_inputs()
            topic_display = inputs["topic_display"]
            topic_slug = inputs["topic_slug"]
            difficulty = inputs["difficulty"]
            url = inputs["url"]

            problem_data = self.extract_problem_details(url)

            if problem_data is None:
                print("\nGemini could not be reached or returned an unusable response.")
                if not self._prompt_yes_no(
                    "Create an empty template problem without Gemini?"
                ):
                    print("Aborted. No files were created.")
                    sys.exit(0)
                manual_title = input("Enter problem title: ").strip()
                if not manual_title:
                    raise ValueError("Title cannot be empty when proceeding without Gemini")
                problem_data = {"title": manual_title, "platform": "Unknown"}

            title = problem_data.get("title", "problem")
            problem_folder_name = self.sanitize_folder_name(title)

            problem_path = self.create_folder_structure(
                topic_slug, difficulty, problem_folder_name
            )

            problem_id = self.get_next_problem_id()

            readme_content = self.format_readme(
                problem_data, url, problem_folder_name, difficulty
            )

            metadata = self.format_metadata(
                problem_data, url, difficulty, topic_display, problem_id
            )

            readme_path = problem_path / "README.md"
            with open(readme_path, "w", encoding="utf-8") as f:
                f.write(readme_content)

            metadata_path = problem_path / "metadata.json"
            with open(metadata_path, "w", encoding="utf-8") as f:
                json.dump(metadata, f, indent=2)

            solution_path = problem_path / "solution.cpp"
            if not solution_path.exists():
                with open(solution_path, "w", encoding="utf-8") as f:
                    f.write("using namespace std;\n\nclass Solution {\n};\n")

            print("\n" + "=" * 60)
            print("✓ Problem template created successfully!")
            print("=" * 60)
            print(f"Problem: {problem_data.get('title', 'Unknown')}")
            print(f"Difficulty: {difficulty}")
            print(f"Topic: {topic_display}")
            print(f"Location: {problem_path}")
            print("\nGenerated files:")
            print(f"  - {readme_path}")
            print(f"  - {metadata_path}")
            print(f"  - {solution_path}")
            print("\nNext steps:")
            print("  1. Review the generated intuition and takeaways")
            print("  2. Implement your solution in solution.cpp")
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
