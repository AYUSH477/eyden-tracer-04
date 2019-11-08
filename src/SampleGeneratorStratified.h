#pragma once

#include "SampleGenerator.h"

class CSampleGeneratorStratified : public CSampleGenerator
{
public:
	virtual void getSamples(int n, float* u, float* v, float* weight) const override
	{
		// --- PUT YOUR CODE HERE ---
		int m = sqrt(n);
		int c = 0;
		float ei, ej;

		for(int i=0; i<m; i++) {
			for(int j=0; j<m; j++) {
				ei = DirectGraphicalModels::random::U<float>(0,1);
				ej = DirectGraphicalModels::random::U<float>(0,1);

				u[c] = (i+ei) / m;
				v[c] = (j+ej) / m;
				c++;
			}
		}
	}
};
