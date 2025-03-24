# Rotate Donut

This repo is inspired by [this article](https://www.a1k0n.net/2011/07/20/donut-math.html).

The mathematical modeling is a little different, I didn't use projection but 
directly mapping.

## Mathematicl Modeling

Briefly introduce it.

- On the xoy plane, the center of a circle is at $(R2, 0, 0)$, its radius is $R1$, 
so any point on it is:
\begin{equation}(x,y,z)=(R_2,0,0)+(R_1\cos\theta,R_1\sin\theta,0)\end{equation}

- Make it rotate around y-axis
\begin{equation}\begin{gathered}
\begin{pmatrix}
R_2+R_1\cos\theta, & R_1\sin\theta, & 0
\end{pmatrix}\cdot
\begin{pmatrix}
\cos\phi & 0 & \sin\phi \\
0 & 1 & 0 \\
-\sin\phi & 0 & \cos\phi
\end{pmatrix} \\
=
\begin{pmatrix}
(R_2+R_1\cos\theta)\cos\phi, & R_1\sin\theta, & -(R_2+R_1\cos\theta)\sin\phi
\end{pmatrix}
\end{gathered}\end{equation}

So we have each point on the donut in 3D space.

- Rotate the object we just got:
\begin{equation}\begin{aligned}&\begin{pmatrix} 
R_2+R_1\cos\theta, & R_1\sin\theta, & 0
\end{pmatrix}\cdot
\begin{pmatrix}
\cos\phi & 0 & \sin\phi \\
0 & 1 & 0 \\
-\sin\phi & 0 & \cos\phi
\end{pmatrix}\cdot\\
&\begin{pmatrix}
1 & 0 & 0 \\
0 & \cos A & \sin A \\
0 & -\sin A & \cos A
\end{pmatrix}\cdot
\begin{pmatrix}
\cos B & \sin B & 0 \\
-\sin B & \cos B & 0 \\
0 & 0 & 1
\end{pmatrix}
\end{aligned}\end{equation}

This is the each point when the donut is at each state$(\theta, \phi, A, B)$.

Then we calculate luminance of each point. Simular from above, if we say the light's 
positive direction is $(0, 1, 1)$(not quite correct this statement, but you know it).

Each point's luminance is, let $R2 = 0, R1 = 1$ in equation above
(means a point on the unit circle), then dot product 
with $(0, 1, 1)/sqrt{2}$.

## Render

We now have each point's coordinate and its luminance, we can render it to the screen now.

I simplify a little. I just took each point's x and y coordinate as the x and y position 
on my terminal, no scaling.

So we should have a offset according to the screen width of the screen of each point's x and 
y.

Besides, two points in the 3D space may map to a same point in 2D space, build a 
data structure called *zbuffer* to store some information, 
just pick the one with larger z coordinate when redering.

Now, in each frame(each A, B), first calculate every point's coordinate, then map it, 
get its x and y on the terminal, finally choose a character(*.,-~:;=!\*#$@*) according to the luminance, 
print the character at the (x, y) position of your terminal, then done.
