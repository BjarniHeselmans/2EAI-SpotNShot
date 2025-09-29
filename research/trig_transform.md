Due to our spot and sensor being in a different place, some transformations have to be done in order for the spotlight to shine on the proper direction.

The sensor does not have a elevation, so only a 2D representation will be given. Therefor some assumptions have to be made. It also results in the placements being more strict.

## Assumptions

- The sensor will be placed on the side of the stage

- The sensor will be perfectly leveled 

- The spotlight will be placed perfectly leveled

- The spotlight may be placed on a different elevation than the sensor

- The location of the spotlight will be measured relative to the sensor (elevation, azimuth and distance)

## Sketch

In our scenario we basically have 3 points of interest. That being the sensor,  the spot and the subject. The easiest way to approach this would be using vectors. As the difference between de vector of the subject to the spot would result in a vector that represents the direction at which the spotlight should look. It then only becomes a matter of how to transform the vector into angles for the spotlight

![](img/Vector%20math.PNG)

The sensor itself can only record angles and a distance to the sensor. These would be polar coordinates and would still need to be transformed to a world coordinates so vectors can be constructed. 

For a more verbose example we can create a simplified sketch of the problem at hand

![](img/distance%20to%20spot.PNG)

## Transformations

### Polar to world coordinates

As it currently stands the IWR1642 example already converts the polar coordinated from sensor to subject to world space coordinates. Making this step redundant.

However, in case we do need too manually convert these polar coordinates to world coordinates the following formula can be used

$$
\begin{aligned}
x &= r\sin(\phi)\cos(\theta) \\
y &= r\sin(\phi)\sin(\theta) \\
z &= r\cos(\phi)
\end{aligned}
$$

Where:
θ = Azimuth (angle that fans out from left to right)

ϕ = Elevation (angle that fans out from top to bottom)

r = Distance from sensor to object

It is possible we need this transformation for creating the vector from the sensor to the spot. As measuring the angles can be performed using a piece of rope and a protractor. This is likely more accurate than measuring the xyz offset from the sensor manually.

### Vectors

The conversion from a points in world space to a vector is quite easy, but if not clear the [Khan academy](https://www.khanacademy.org/math/linear-algebra/vectors-and-spaces/vectors/v/vector-introduction-linear-algebra) provides a good research for a introduction to vector maths.

We need to create a vector from the sensor to the subject and from the sensor to the spotlight. Since the spotlight is on (0,0,0) the point basically becomes the vector

We then subtract the sensor to spotlight vector from the sensor to subject. This leaves us with a vector from the camera to the subject.

### Angle of spotlight

Now we have a vector in the right direction we need to convert this vector into the right angles again. The only tricky part here might be that our spotlight isn't positioned in the same direction as the sensor. So it is possible we need to subtract a angle from the result in order to achieve the right rotations.

For the transformation we need to do the first in reverse

$$
\begin{aligned}
r &= \sqrt{x^2 + y^2 + z^2} \\
\theta &= \tan^{-1} \left(\frac{y}{x}\right) \\
\phi &= \cos^{-1} \left(\frac{z}{r}\right)
\end{aligned}
$$

Where with our spotlight ​θ is the rotation from it's first joint

ϕ would then be the rotation from the second joint/tilt

In our case we can ignore distance after having calculated ϕ but this can potentially be useful if we ever decide to upgrade to a spotlight with a focus mechanism.

## Possible speed-ups

The steps highlighted above are multi-step processes and are quite computationally heavy. Transformations like this are quite common in game development so looking into a solution from this sector might help trying to find a speed-up to the solution if this becomes a problem.

Perhaps we could also look into offloading other computations to the other core and using the stronger and fast core for the SPI communication and data transformation.
