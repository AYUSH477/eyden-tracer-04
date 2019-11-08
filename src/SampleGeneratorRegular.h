#pragma once

#include "SampleGenerator.h"

class CSampleGeneratorRegular : public CSampleGenerator
{
public:
	virtual void getSamples(int n, float* u, float* v, float* weight) const override
	{
		// --- PUT YOUR CODE HERE ---
		int m = sqrt(n);
		int c = 0;

		for(int i=0; i<m; i++) {
			for(int j=0; j<m; j++) {
				u[c] = (i+0.5f) / m;
				v[c] = (j+0.5f) / m;
				c++;
			}
		}

	}
};
