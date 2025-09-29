inline double fast_pow_int(const double base, const uniform int exponent) {
    if (exponent == 1) return base;
    if (exponent == 2) return base * base;
    if (exponent == 3) return base * base * base;
    if (exponent == 4) { double b2 = base * base; return b2 * b2; }
    if (exponent == 5) { double b2 = base * base; return b2 * b2 * base; }
    
    double result = 1.0;
    double power = base;
    uniform int n = exponent;
    while (n > 0) {
        if (n & 1) result *= power;
        power *= power;
        n >>= 1;
    }
    return result;
}

inline int findClosestRoot(
    const double zr, 
    const double zi,
    const uniform int n,
    const uniform double rootsRe[],
    const uniform double rootsIm[]
) {
    double minDist = (zr - rootsRe[0])*(zr - rootsRe[0]) + (zi - rootsIm[0])*(zi - rootsIm[0]);
    int rootIndex = 0;
    
    for (uniform int k = 1; k < n; k++) {
        double dist = (zr - rootsRe[k])*(zr - rootsRe[k]) + (zi - rootsIm[k])*(zi - rootsIm[k]);
        if (dist < minDist) {
            minDist = dist;
            rootIndex = k;
        }
    }
    
    return rootIndex;
}

export void render(
    const uniform int width,
    const uniform int height,
    const uniform int n,
    const uniform int maxIter,
    const uniform double xmin,
    const uniform double xmax,
    const uniform double ymin,
    const uniform double ymax,
    const uniform double rootsRe[],
    const uniform double rootsIm[],
    uniform uint8 rPlane[],
    uniform uint8 gPlane[],
    uniform uint8 bPlane[]
) {
    uniform double dx = (xmax - xmin) / (width - 1);
    uniform double dy = (ymax - ymin) / (height - 1);
    uniform float inv_maxIter = 1.0f / maxIter;
    
    for (uniform int py = 0; py < height; py++) {
        uniform double y = ymin + dy * py;
        
        foreach(px = 0 ... width) {
            double x = xmin + dx * px;
            double zr = x;
            double zi = y;
            
            varying int iter = 0;
            
            for (uniform int step = 0; step < maxIter; step++) {
                double r2 = zr*zr + zi*zi;
                double r = sqrt(r2);
                double theta = atan2(zi, zr);
                
                // f(z) = z^n - 1
                double rn = fast_pow_int(r, n);
                double ntheta = n * theta;
                double fRe = rn * cos(ntheta) - 1.0;
                double fIm = rn * sin(ntheta);
                
                // f'(z) = n * z^(n-1)
                double rn1 = (n == 1) ? 1.0 : rn / r;
                double n1theta = (n-1) * theta;
                double dfRe = n * rn1 * cos(n1theta);
                double dfIm = n * rn1 * sin(n1theta);
                
                double denom = dfRe*dfRe + dfIm*dfIm;
                
                if (denom >= 1e-12) {
                    double inv_denom = 1.0 / denom;
                    double zrNext = zr - (fRe*dfRe + fIm*dfIm) * inv_denom;
                    double ziNext = zi - (fIm*dfRe - fRe*dfIm) * inv_denom;
                    double delta2 = (zrNext-zr)*(zrNext-zr) + (ziNext-zi)*(ziNext-zi);
                    
                    if (delta2 >= 1e-12) {
                        zr = zrNext;
                        zi = ziNext;
                        iter++;
                    } else {
                        break;
                    }
                } else {
                    break;
                }
            }
            
            int rootIndex = findClosestRoot(zr, zi, n, rootsRe, rootsIm);
            
            int brightness = (int)(255.0f * (1.0f - (float)iter * inv_maxIter));
            int colorIdx = rootIndex;
            while (colorIdx >= 3) colorIdx -= 3;
            
            int idx = py * width + px;
            rPlane[idx] = (colorIdx == 0) ? brightness : 0;
            gPlane[idx] = (colorIdx == 1) ? brightness : 0;
            bPlane[idx] = (colorIdx == 2) ? brightness : 0;
        }
    }
}