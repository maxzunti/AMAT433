#include <fourier.h>

// Perform a Fourier transform on z(t) = cos(t) + isin(t)
std::vector<double[2]> performTransform(std::vector<double> xVals, std::vector<double> yVals) {
    // Get size N
    int N = xVals.size();
    N == yVals.size()? : std::cout << "Different vector sizes" << std::endl;

    // Complex arrays to store inputs and outputs
    fftw_complex *in, *out;
    in = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * N);
    out = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * N);
    for (int i = 0; i < N; i++) {
        in[i][0] = xVals[i];   // reals
        in[i][1] = yVals[i];   // ims
    }

    // fftw planner for optimization
    // Run no computational tests
    fftw_plan p = fftw_plan_dft_1d(N, in, out, FFTW_FORWARD, FFTW_ESTIMATE);

    fftw_execute(p);
    std::vector<double[2]> output(out, out + N);
    for (int i = 0; i < output.size(); i++) {
     //   std::cout << "OUT =" << out[i][0] << std::endl;
        std::cout << "real [" << i << "] == " << out[i][0] << "\tim = " << out[i][1] << std::endl;
    }

    fftw_destroy_plan(p);

    if (output.size() != N)
        std::cout << "Output has wrong size" << std::endl;

    // Free memory
    fftw_free(in);
    fftw_free(out);

    return output;
}

std::vector<double[2]> performReTransform(std::vector<double> reals) {
    // Get size N
    int N = reals.size();

    // Complex arrays to store inputs and outputs
    fftw_complex *in, *out;
    in = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * N);
    out = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * N);
    for (int i = 0; i < N; i++) {
        in[i][0] = reals[i];   // reals
        in[i][1] = 0;   // ims
    }

    // fftw planner for optimization
    // Run no computational tests
    fftw_plan p = fftw_plan_dft_1d(N, in, out, FFTW_FORWARD, FFTW_ESTIMATE);

    fftw_execute(p);
    std::vector<double[2]> output(out, out + N);
    for (int i = 0; i < output.size(); i++) {
     //   std::cout << "OUT =" << out[i][0] << std::endl;
      //  std::cout << "real [" << i << "] == " << out[i][0] << "\tim = " << out[i][1] << std::endl;
    }

    fftw_destroy_plan(p);

    if (output.size() != N)
        std::cout << "Output has wrong size" << std::endl;

    // Free memory
    fftw_free(in);
    fftw_free(out);

    return output;

}

std::vector<double> getMags(std::vector<double[2]> transformed_vals) {
    std::vector<double> mags;
    for (int i = 0; i < transformed_vals.size(); i++) {
        mags.push_back(sqrt(
                    (transformed_vals[i][0] * transformed_vals[i][0]) +
                    (transformed_vals[i][1] * transformed_vals[i][1]))
                );
    }
    return mags;
}

std::vector<double> normalize(std::vector<double> in_vec) {
    double max = in_vec[getMaxIndex(in_vec, false, 0, in_vec.size() - 1)];
    double abs_min = in_vec[getMaxIndex(in_vec, true, 0, in_vec.size() - 1)];
    if (abs_min < 0)
        abs_min *= -1.0;
    if (abs_min > max) {
        max = abs_min;
    }

    for (int i = 1; i < in_vec.size(); i++) {
        in_vec[i] = in_vec[i] / max;
    }
    return in_vec;
}

int getMaxIndex(std::vector<double> vec, bool negative, int minIndex, int maxIndex) {
    double max = 0;
    int index = -1;
    if (maxIndex >= vec.size()) {
        std::cerr << "maxIndex out of range" << std::endl;
        return -1;
    }
    for (int i = minIndex; i <= maxIndex; i++) {
        if (negative) {                             // Lowest num
            if (vec[i] < max) {
                max = vec[i];
                index = i;
            }
        } else {                                    // Highest num
            if (vec[i] > max) {
                max = vec[i];
                index = i;
            }
        }
    }
    return index;
}

std::vector<double> getPhase(std::vector<double[2]> transformed_vals) {
    std::vector<double> phase;
    for (int i = 0; i < transformed_vals.size(); i++) {
        phase.push_back(atan2(transformed_vals[i][1], transformed_vals[i][0]));
    }
    return phase;
}

