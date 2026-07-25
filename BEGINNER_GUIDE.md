# 🎨 CAitSith 3D AI Character Designer — Beginner's Manual

Welcome to **CAitSith**! This guide will walk you step-by-step through generating, sculpting, lighting, and exporting 3D character models—even if you have never used 3D software before.

---

## 📍 Quick Overview: How It Works

```
1. Type a Prompt  ➡️  2. AI Generates 3D Mesh  ➡️  3. Sculpt & Refine Details  ➡️  4. Adjust Light & Export (.OBJ / .STL)
```

---

## 🚀 Step 1: Launching the Application

Open your terminal or command prompt inside the project folder and run:

```bash
./CAitSithApp
```

Upon startup, CAitSith will load:
- An **Orbit Camera** centered on your character.
- A **3D Viewport** with real-time lighting.
- A **Base Poly-Mesh** sphere ready for editing.
- The **Sculpting & AI Engine**.

---

## 🎥 Step 2: Navigating the 3D Viewport

Controlling your view and light source is key to sculpting details.

| Action | Controls | What it Does |
| :--- | :--- | :--- |
| **Rotate (Orbit)** | Left-Click + Drag | Rotates the camera 360° around your character model. |
| **Pan View** | Right-Click + Drag (or Shift + Drag) | Moves the camera up, down, left, or right. |
| **Zoom In / Out** | Mouse Scroll Wheel | Zooms closer to inspect fine details or zooms out for a full view. |
| **Move Light Source** | `Light Position Sliders` in UI | Moves the sun/light in 3D space to highlight shadows and muscle details. |

---

## 🤖 Step 3: Generating 3D Characters with AI

Instead of building a character from scratch, let AI create the base model for you!

1. Open the **AI Generation Panel** in the UI.
2. Type a descriptive text prompt into the **Prompt Box**.
   - *Example*: `"Cyberpunk samurai warrior with futuristic shoulder armor"`
   - *Example*: `"Fantasy dwarf paladin holding a battle axe"`
3. Select your preferred **Target Polygon Count** (default: `15,000` triangles).
4. Click **[Generate 3D Character]**.
5. Wait a few seconds for the AI engine to generate and load the model directly into your 3D viewport.

---

## 🖌️ Step 4: Digital Sculpting & Editing Tools

Once your model is loaded, use sculpting tools to shape it like digital clay.

### Available Brushes:

1. 🧱 **Clay / Inflate Brush**
   - **What it does**: Pulls material outward to build up muscles, armor plates, or facial features.
   - **Best for**: Adding volume and shaping body forms.

2. 🌊 **Smooth Brush**
   - **What it does**: Blends rough surfaces into clean, smooth geometry.
   - **Best for**: Removing bumps, skin smoothing, and clean curves.

3. 📐 **Flatten Brush**
   - **What it does**: Presses geometry flat against a surface plane.
   - **Best for**: Creating sharp armor edges, weapons, and mechanical parts.

4. ✋ **Grab / Move Brush**
   - **What it does**: Pulls and stretches parts of the mesh in any direction.
   - **Best for**: Adjusting character proportions, extending horns, or posing limbs.

5. ✂️ **Trim / Slice Plane**
   - **What it does**: Shaves off unwanted sections above a cutting line.
   - **Best for**: Creating flat bases for 3D printing or trimming extra geometry.

### Brush Sliders:
- **Radius**: Controls how large or small your brush area is.
- **Strength**: Controls how strong or subtle each brush stroke is.

---

## 💾 Step 5: Saving & Exporting Your Design

When you are satisfied with your character model:

1. Open the **File Manager Panel**.
2. Type your desired file name (e.g., `my_character.obj`).
3. Choose your export format:
   - **Export as .OBJ**: Best for opening in **Blender**, **Unreal Engine**, **Unity**, or **Maya**.
   - **Export as .STL**: Best for **3D Printing** software (Slicers like Cura or PrusaSlicer).
4. Click **[Save File]**.

---

## 📂 Step 6: Opening & Editing Existing 3D Files

Have a `.obj` model from another tool that you want to adjust?

1. Place your `.obj` file inside the project directory.
2. Type the filename into the **Import Box** (e.g., `hero.obj`).
3. Click **[Open Model]**.
4. Use the camera, lighting, and sculpting tools to make your adjustments!

---

## 💡 Beginner Tips for Great Results

> [!TIP]
> **Lighting is Everything**: Rotate your light source while sculpting to easily spot uneven surfaces and shadows.

> [!TIP]
> **Start Big, Then Detail**: Use the **Grab** tool first to fix overall proportions before adding details with the **Clay** and **Smooth** brushes.

> [!TIP]
> **Undo & Soft Strokes**: Keep your brush strength around `0.20` for smooth, controlled sculpting.
