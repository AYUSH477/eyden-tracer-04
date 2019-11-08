#pragma once

#include "SampleGenerator.h"
#include "random.h"

class CSampleGeneratorRandom : public CSampleGenerator
{
public:
	virtual void getSamples(int n, float* u, float* v, float* weight) const override
	{
		// --- PUT YOUR CODE HERE ---
		float tmp_u, tmp_v;
		for(int i=0; i<n; i++) {
			tmp_u = DirectGraphicalModels::random::U<float>(0,1);
			tmp_v = DirectGraphicalModels::random::U<float>(0,1);

			u[i] = tmp_u;
			v[i] = tmp_v;
			weight[i] = 1.0f/n;
		}
	}
};


