# Communication Rubric — Axis 2

> Content is *what* you say ([the 7 beats](interview-explanation-template.md)). This is *how* you say it. **Both are graded in a real interview.** Added 2026-08-16.

Score each dimension **/5**, total **/30**.

---

## The six dimensions

| # | Dimension | 5 = | 1 = |
|---|---|---|---|
| 1 | **Structure & signposting** | Named beats out loud — *"The key observation is…"*, *"Let me trace…"*, *"For complexity…"* | Stream of consciousness, no transitions |
| 2 | **Terminology precision** | Exact technical words, used consistently | Wrong or drifting terms — set/map, subset/superset |
| 3 | **Conciseness** | Every sentence earns its place | Repetition, filler clauses, 3× the needed words |
| 4 | **Fluency** | Silent pauses instead of fillers; no false starts | "until until", "not not", stutter-repeats |
| 5 | **Confidence** | States correct things flatly | "I think", "I guess", "it's a simple solution", "just" |
| 6 | **Listener-tracking** | Followable in one pass, no rewinding | Sentences that can't be parsed |

**Note:** speech-to-text garbles are *not* scored. Only what you actually said.

---

## Score log

| Date | Problem | 1 Struct | 2 Term | 3 Concise | 4 Fluency | 5 Confid | 6 Track | **Total** |
|---|---|---|---|---|---|---|---|---|
| 2026-08-16 | Minimum Window Substring | 3 | 2 | 2 | 2 | 2 | 2 | **13/30** |
| 2026-08-20 | Sliding Window Maximum | 3.5 | 2 | 3 | 3 | **4** ⬆️ | 3 | **18.5/30** |

---

## Active fixes (work these in order)

### 0. 🔴 DIRECTION INVERSION — the #1 fix

**Three explanations, three inversions — with correct code every time.**

| Said | Actually |
|---|---|
| "eliminate where s2's length is **greater** than s1" | s1 greater than s2 |
| "frequency **subset**" | super**set** — the window *covers* t |
| "maintain an always **increasing** sequence" | **decreasing** — the front is the max |

This is not a comprehension gap. It's a missing *verbal label*: with no rehearsed phrase for the direction, you derive it live and land it about half the time.

**Fix: anchor to a concrete position. Never name a direction.**

> ❌ "we maintain a decreasing sequence"
> ✅ **"the front of the deque always holds the window's maximum"**

A concrete anchor cannot be inverted. Rewrites for the others:
- ✅ "we bail out when t is longer than s"
- ✅ "the window has to contain every character t needs"

**Rehearse the anchored phrase. Do not derive the direction while speaking.**

### 1. ⚠️ Terminology — the expensive one

A confused interviewer stops awarding credit. This costs more than every filler combined.

| Said | Should be | Why |
|---|---|---|
| "frequency **set**" | frequency **map** / **counter** | sets don't hold counts |
| "**substring** of the frequency set" | **covers** / **contains** | "substring" already means the answer here |
| "**subset**" | **superset** — `window[c] ≥ need[c]` | the relation runs the other way |

**Rule: if a word already means something specific in this problem, never reuse it for something else.**

### 2. Don't hedge what you got right

All four "I think"s landed in the complexity section — which was **correct**. Hedging a right answer converts it into a guess in the listener's mind.

> ❌ "I think we are going two times n worth of operations, so I think the complexity is O(n) I guess"
> ✅ "Each character is added once and removed at most once, so it's O(n) amortized."

Reserve "I think" for things you're actually unsure of. Then it carries real information.

### 3. Cut the minimizing words

`just` · `simple` · `very easy` · `that's about it`. Every one shrinks your own work. Delete them; the sentence is stronger without.

### 4. Cap sentences at ~20 words

Every unparseable passage so far has been a 30+ word sentence — **P4 in the English profile, composing past your buffer.** Full stop, breathe, next sentence. Shorter sentences fix fluency, listener-tracking, and conciseness simultaneously.

---

## Self-check before speaking

- [ ] Do I know the exact word for each concept — and am I using it consistently?
- [ ] Am I about to hedge something I actually know?
- [ ] Is this sentence under 20 words?
- [ ] Silence instead of "um"?
