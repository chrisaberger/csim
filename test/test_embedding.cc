#include "third_party/catch/catch.hpp"
#include "tensor.h"
#include "layers/embedding.h"
#include <limits>

TEST_CASE("Testing embedding lookups", "[float_embeddings]") {
  const size_t num_words = 9;
  const size_t emb_dim = 10;
  Tensor<size_t> input = Tensor<size_t>::from_vec({7, 1, 8, 2, 5}, {5});
  Embedding<float> emb =
      Embedding<float>(Tensor<float>::from_npy("../test/data/embedding.npy"));

  Tensor<float> dec = emb.forward(input);

  typedef std::numeric_limits< double > dbl;
  std::cout.precision(dbl::max_digits10);

  Tensor<float> baseline_dec = Tensor<float>::from_vec(
      {1.6734272241592407,   0.010342830792069435, -0.70395666360855103,
       -0.18526579439640045, -0.34157752990722656, -0.30025827884674072,
       1.3075355291366577,   -1.1627987623214722,  0.11963611096143723,
       -0.1631353348493576,  -0.77731430530548096, -0.25145524740219116,
       -0.22227048873901367, 1.6871134042739868,   0.22842517495155334,
       0.46763551235198975,  -0.69697242975234985, -1.1607614755630493,
       0.69954240322113037,  0.19908162951469421,  0.66144531965255737,
       1.1899205446243286,   1.4301451444625854,   0.42077338695526123,
       -0.35380652546882629, 0.76392704248428345,  -0.58895069360733032,
       -0.76359736919403076, 1.3352056741714478,   0.60427361726760864,
       0.8656923770904541,   0.24440392851829529,  -0.66291135549545288,
       0.80730825662612915,  1.1016806364059448,   -0.17593604326248169,
       -2.2455577850341797,  -1.4464579820632935,  0.061155281960964203,
       -0.61774450540542603, 0.066280260682106018, -0.43704012036323547,
       0.7626006007194519,   0.44151091575622559,  1.1651384830474854,
       2.0153918266296387,   0.13741245865821838,  0.93864470720291138,
       -0.18600109219551086, -0.64463931322097778},
      {5, 10});

  for(size_t i = 0; i < input.numel; ++i){
    Tensor<float> cur_row = emb.weight.view(input[i], input[i]+1);
    for(size_t j = 0; j < emb_dim; ++j){
      REQUIRE(cur_row[j] == dec(i,j));
      REQUIRE(baseline_dec[i * emb_dim + j] == dec(i, j));
    }
  }
}
