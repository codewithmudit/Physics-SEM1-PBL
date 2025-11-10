# 🔬 Newton's Rings Simulator (C Language)

A simple **C-based simulator and calculator** for the *Newton’s Rings experiment* — a classic physics optics setup used to determine the **wavelength of light** and **radius of interference rings**.

This program uses standard formulas from the lab handout and allows you to:
- Calculate the **wavelength (λ)** of a sodium light source using measured ring diameters.
- Compute the **radius or diameter of the nth bright ring** for a given light wavelength.
- Change the **refractive index (μ)** to simulate different media (e.g., air, water, oil).

---

## ⚙️ Features
- Computes wavelength from measured diameters \( D_n \) and \( D_{n+p} \)
- Computes radius \( r_n \) or diameter \( D_n \) of the nth bright ring
- Allows refractive index input to simulate different media
- Handles invalid inputs safely
- Fully terminal-based, cross-platform compatible
- Uses SI units internally (mm → m conversion handled automatically)

---

## 🧪 Formulas Used

From the Newton’s Rings experiment derivations:

\[
\lambda_{\text{medium}} = \frac{D_{n+p}^2 - D_n^2}{4 p R}
\]

\[
r_n = \sqrt{\frac{(2n - 1)\lambda_{\text{medium}} R}{2}}
\]

Where:
- \( \lambda_{\text{medium}} \) = wavelength in the medium  
- \( R \) = radius of curvature of the lens  
- \( D_n, D_{n+p} \) = diameters of nth and (n+p)th rings  
- \( p \) = difference in ring orders  
- \( μ \) = refractive index of the medium  
- \( λ_{\text{vacuum}} = μ \times λ_{\text{medium}} \)

---

## 💻 Compilation & Execution

### **Compile**
```bash
gcc newton_rings_sim.c -o newton_rings_sim -lm
