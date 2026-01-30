# FDF - Wireframe 3D Renderer

A high-performance 3D wireframe visualization tool written in C that transforms heightmap data into interactive isometric projections. This project demonstrates low-level graphics programming, mathematical transformations, and real-time rendering using the MiniLibX graphics library.

## Table of Contents

- [Overview](#overview)
- [Features](#features)
- [Project Structure](#project-structure)
- [Installation](#installation)
- [Usage](#usage)
- [Technical Details](#technical-details)
- [Controls](#controls)
- [Limitations & Notes](#limitations--notes)
- [License](#license)

## Overview

FDF (Fil de Fer, French for "wireframe") is a 3D graphics project that reads elevation maps from text files and renders them as interactive wireframe models. The program performs real-time 3D transformations including rotation, translation, scaling, and projection, all implemented from scratch without external 3D libraries.

This project solves the fundamental computer graphics challenge of converting 3D coordinates into 2D screen space while maintaining visual depth through isometric projection. It emphasizes efficient memory management, mathematical precision, and smooth user interaction in a resource-constrained environment.

**Why it exists**: Part of the 42 School curriculum, FDF teaches the fundamentals of graphics programming, matrix transformations, and event-driven programming—skills essential for game development, computer vision, and graphics-intensive applications.

## Features

### Core Functionality
- **Map parsing**: Reads heightmap files in custom format (integers representing altitude)
- **3D projection**: Implements isometric projection with configurable viewing angles
- **Bresenham's line algorithm**: Efficient rasterization for wireframe drawing
- **Color interpolation**: Smooth gradient transitions between vertices
- **Custom color support**: Parse hexadecimal color values from map files
- **Dynamic palette**: Automatic color generation based on altitude
- **Real-time rendering**: Interactive frame-by-frame updates at high performance

### Interactive Controls
- **Translation**: Pan the model in all directions
- **Rotation**: Rotate around X, Y, and Z axes independently
- **Zoom**: Scale the model dynamically
- **Z-axis scaling**: Adjust terrain elevation independently
- **View presets**: Quick switch between isometric and orthographic views
- **Color toggle**: Switch between map-defined and altitude-based coloring
- **On-screen menu**: Real-time display of current transformations and controls

### Bonus Features
- Enhanced color palette with 11 gradient levels
- Menu overlay with control instructions
- Multiple projection modes
- Smooth color interpolation along line segments
- Memory-efficient double-buffering

## Project Structure

```
fdf/
├── fdf.h                      # Main header with structures and prototypes
├── fdf_bonus.h                # Bonus features header
├── fdf_main.c                 # Program entry point and initialization
├── fdf_parse_map.c            # Map file parser and validator
├── fdf_parse_color.c          # Hexadecimal color parsing
├── fdf_draw_win.c             # Line drawing and projection logic
├── fdf_map_view.c             # Transformation and view management
├── fdf_loop_hook.c            # Main rendering loop
├── fdf_key_utils.c            # Keyboard event handlers
├── fdf_axis_locations.c       # 3D rotation matrix operations
├── fdf_init_map.c             # Map initialization and memory allocation
├── fdf_alloc_free.c           # Memory management utilities
├── fdf_error_check.c          # Input validation and error handling
├── fdf_set_menu.c             # On-screen menu rendering
├── fdf_utils.c                # Helper functions (min, max, percent)
├── ft_atoi_base.c             # Base conversion for color parsing
├── Makefile                   # Build configuration
├── libft/                     # Custom C standard library
├── printf/                    # Custom printf implementation
├── get_next_line/             # File reading utility
└── mlx/                       # MiniLibX graphics library
```

### Key Files

- **fdf_draw_win.c**: Implements Bresenham's algorithm and isometric projection
- **fdf_parse_map.c**: Validates map format and builds 3D point grid
- **fdf_map_view.c**: Handles all user input and transformation calculations
- **fdf_axis_locations.c**: Matrix multiplication for 3D rotations
- **fdf.h**: Defines core structures (`t_map`, `t_fdf`, `t_point`, `t_mpoint`)

## Installation

### Prerequisites

- **Compiler**: GCC or Clang
- **Build System**: GNU Make
- **Graphics Library**: MiniLibX (X11/OpenGL wrapper)
- **OS**: Linux (X11) or macOS
- **Dependencies**: X11 development libraries (`libx11-dev`, `libxext-dev`)

### System-Specific Setup

**Linux (Ubuntu/Debian):**
```bash
sudo apt-get update
sudo apt-get install gcc make libx11-dev libxext-dev libbsd-dev
```

**macOS:**
```bash
# XCode Command Line Tools required
xcode-select --install
```

### Building the Project

```bash
# Clone the repository
git clone <repository-url>
cd fdf

# Build mandatory part
make

# Build bonus features
make bonus

# Build with Valgrind memory checking
make valgrind_fdf ARGS="maps/42.fdf"
```

The Makefile automatically clones required dependencies:
- `libft` - Custom C library implementation
- `printf` - Custom ft_printf function
- `get_next_line` - Line-by-line file reader
- `mlx` - MiniLibX graphics library
- `maps` - Sample heightmap files

### Makefile Targets

- `make` - Compile mandatory version
- `make bonus` - Compile with bonus features
- `make clean` - Remove object files
- `make fclean` - Remove objects and executables
- `make re` - Rebuild from scratch
- `make valgrind_fdf` - Run with memory leak detection
- `make clear` - Remove all dependencies (full clean)

## Usage

### Basic Execution

```bash
./fdf <map_file>
```

### Example Commands

```bash
# Render a simple map
./fdf maps/42.fdf

# Render complex terrain
./fdf maps/mars.fdf

# Bonus version with enhanced features
./fdf_bonus maps/pylone.fdf
```

### Map File Format

Maps are text files where each number represents a point's altitude:

```
0  0  0  0  0  0  0  0  0  0
0  0  0  0  0  0  0  0  0  0
0  0 10 10  0  0 10 10  0  0
0  0 10 10  0  0 10 10  0  0
0  0  0  0  0  0  0  0  0  0
```

**With custom colors:**
```
0  0  0  0  0  0  0  0  0  0
0  0  0  0  0  0  0  0  0  0
0  0 10,0xFF0000 10  0  0 10 10  0  0
0  0 10 10  0  0 10 10  0  0
0  0  0  0  0  0  0  0  0  0
```

Color format: `altitude,0xRRGGBB` (hexadecimal RGB)

### Expected Output

- Opens a 1920x1080 window
- Displays wireframe model in isometric view
- Shows control menu on screen (bonus)
- Responds to keyboard input for transformations
- Smooth color gradients based on altitude

## Technical Details

### Algorithms & Techniques

#### Bresenham's Line Algorithm
Efficient integer-only line rasterization without floating-point operations:
```c
// Core logic: incremental decision-making
error = abs(dx) - abs(dy);
while (not at endpoint) {
    plot_pixel(x, y);
    if (2*error > -dy) { x += sx; error -= dy; }
    if (2*error < dx)  { y += sy; error += dx; }
}
```

**Why Bresenham?**
- No floating-point arithmetic (faster on older hardware)
- Perfect pixel accuracy
- Minimal memory footprint
- Suitable for real-time rendering

#### Isometric Projection
Transforms 3D coordinates to 2D screen space using rotation matrices:

```c
// Alpha and beta define viewing angles
x_screen = (x * zoom - y * zoom) * cos(alpha) + x_offset;
y_screen = (-z * zoom + (x * zoom + y * zoom) * sin(beta)) + y_offset;
```

**Rotation Matrices:**
- X-axis rotation (pitch)
- Y-axis rotation (yaw)
- Z-axis rotation (roll)

Each implemented via trigonometric matrix multiplication.

#### Color Interpolation
Linear interpolation between vertex colors along line segments:
```c
color = start_color + (end_color - start_color) * (current_step / total_steps)
```

Produces smooth gradients without banding artifacts.

### Memory Management

**Allocation Strategy:**
- 2D array of points allocated in contiguous blocks
- Separate map point (`t_mpoint`) and projected point (`t_point`) structures
- All memory freed before program exit (verified with Valgrind)

**Data Structures:**
```c
typedef struct s_map {
    int rows, cols;                  // Map dimensions
    int high, deep;                  // Min/max altitude
    t_mpoint **mgrid;                // Original 3D points
    t_point **grid;                  // Projected 2D points
    double x_rotate, y_rotate, z_rotate;  // Rotation angles
    double zoom, zscale;             // Scaling factors
    double x_offset, y_offset;       // Translation
    // ... projection parameters
} t_map;
```

**Memory Safety:**
- No memory leaks (Valgrind clean)
- Bounds checking on array access
- Graceful error handling with cleanup
- Double-free protection

### Performance Optimizations

- **Integer arithmetic**: Bresenham's algorithm avoids slow floating-point
- **Dirty rectangle**: Only redraws when transformations occur
- **Direct pixel manipulation**: Writes to image buffer, not individual pixel calls
- **Precomputed values**: Trigonometric functions cached per frame
- **Efficient loop structure**: Minimal function call overhead in hot paths

### System Calls & Libraries

**MiniLibX Functions:**
- `mlx_init()` - Initialize graphics connection
- `mlx_new_window()` - Create display window
- `mlx_new_image()` - Allocate image buffer
- `mlx_loop_hook()` - Register render callback
- `mlx_hook()` - Register event handlers
- `mlx_put_image_to_window()` - Display frame buffer

**Standard Library:**
- `open()`, `read()`, `close()` - File I/O
- `malloc()`, `free()` - Dynamic memory
- `sin()`, `cos()` - Trigonometric calculations (math.h)

**Custom Implementations:**
- `ft_atoi_base()` - Hexadecimal parsing
- `get_next_line()` - Line-by-line file reading
- `ft_printf()` - Formatted output

### Design Constraints

**42 School Requirements:**
- Must use MiniLibX (no OpenGL, DirectX, or Vulkan)
- Norm compliant (strict coding standards)
- No memory leaks or invalid reads/writes
- Handle edge cases (empty maps, invalid formats)
- Smooth window close without crashes

## Controls

### Keyboard Shortcuts

| Key | Action |
|-----|--------|
| **Arrow Keys** | Pan (translate) the model |
| `+` / `-` | Zoom in / out |
| `*` | Zoom out (alternative) |
| `T` / `G` | Increase / decrease Z-axis scale |
| `S` | Rotate around X-axis (pitch) |
| `D` | Rotate around Y-axis (yaw) |
| `A` | Rotate around Z-axis (roll) |
| `Q` | Rotate around X-axis (opposite direction) |
| `W` | Rotate around Y-axis (opposite direction) |
| `E` | Rotate around Z-axis (opposite direction) |
| `1` | Reset to default isometric view |
| `2` | Switch to orthographic view |
| `3` | Toggle color mode (map colors vs altitude palette) |
| `ESC` | Exit program |

**Note**: All rotations and transformations are cumulative and reversible.

## Limitations & Notes

### Known Limitations

- **Window size**: Fixed at 1920x1080 (defined in header)
- **Map size**: Performance degrades on maps larger than 1000x1000 points
- **Projection clipping**: Points outside window bounds are not drawn (no clipping plane)
- **Z-fighting**: Overlapping lines at identical depths may flicker
- **No anti-aliasing**: Lines may appear jagged at certain angles
- **Color depth**: Limited to 24-bit RGB (no alpha transparency in rendering)

### Edge Cases Handled

- **Empty files**: Proper error message and cleanup
- **Irregular maps**: Validates that all rows have same column count
- **Invalid colors**: Defaults to gray (0x808080) if parsing fails
- **Extremely large values**: Protected against integer overflow
- **Missing map files**: Checks file extension (.fdf) and readability

### Design Decisions

- **Separate bonus version**: Cleaner codebase for evaluation
- **Isometric default**: More visually interesting than orthographic
- **Color palette**: Vibrant purple/pink gradient for aesthetic appeal
- **Menu overlay**: Uses MLX string rendering (not drawn to image buffer)
- **Rotation angles**: Uses radians internally for trigonometric functions

### Not Implemented

- **Perspective projection** (only isometric/orthographic)
- **Hidden surface removal** (all lines always visible)
- **Texture mapping**
- **Lighting/shading calculations**
- **Mouse controls** (keyboard only per project requirements)
- **Animation recording** or screenshot export

## Compiler Flags

```makefile
CFLAGS = -Wall -Wextra -Werror -g
```

- **-Wall**: Enable all standard warnings
- **-Wextra**: Enable extra warnings
- **-Werror**: Treat warnings as errors (strict quality)
- **-g**: Include debug symbols (for GDB/Valgrind)

**Linking Flags:**
```makefile
-lm -lXext -lX11
```
- **-lm**: Math library (sin, cos, sqrt)
- **-lXext**: X11 extensions
- **-lX11**: X11 graphics library

## License

This project is for educational purposes as part of the 42 School curriculum. All code is original implementation adhering to strict academic integrity standards.

---

**Technical Highlights for Recruiters:**

This project demonstrates proficiency in:
- **Low-level graphics programming** without high-level abstractions
- **Mathematical transformations** (matrix operations, projections)
- **Memory management** in C (manual allocation, deallocation, leak prevention)
- **Algorithm implementation** (Bresenham's line, color interpolation)
- **Event-driven architecture** (real-time input handling)
- **Performance optimization** (integer arithmetic, minimal syscalls)
- **Code organization** in large C projects (modularity, header management)

Relevant for roles in: **Graphics Programming, Game Development, Systems Programming, Embedded Systems, Computer Vision, Scientific Computing**
