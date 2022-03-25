// Copyright (c) by respective owners including Yahoo!, Microsoft, and
// individual contributors. All rights reserved. Released under a BSD (revised)
// license as described in the file LICENSE.
#include "shared_data.h"

#include "best_constant.h"
#include "loss_functions.h"
#include "memory.h"
#include "named_labels.h"
#include "parse_primitives.h"
#include "table_formatter.h"
#include "text_utils.h"

#include <algorithm>
#include <cfloat>
#include <climits>
#include <iomanip>

shared_data::shared_data(const shared_data& other)
{
  queries = other.queries;
  example_number = other.example_number;
  total_features = other.total_features;
  t = other.t;
  weighted_labeled_examples = other.weighted_labeled_examples;
  old_weighted_labeled_examples = other.old_weighted_labeled_examples;
  weighted_unlabeled_examples = other.weighted_unlabeled_examples;
  weighted_labels = other.weighted_labels;
  sum_loss = other.sum_loss;
  sum_loss_since_last_dump = other.sum_loss_since_last_dump;
  dump_interval = other.dump_interval;
  gravity = other.gravity;
  contraction = other.contraction;
  min_label = other.min_label;
  max_label = other.max_label;
  if (other.ldict) { ldict = VW::make_unique<VW::named_labels>(*other.ldict); }
  weighted_holdout_examples = other.weighted_holdout_examples;
  weighted_holdout_examples_since_last_dump = other.weighted_holdout_examples_since_last_dump;
  holdout_sum_loss_since_last_dump = other.holdout_sum_loss_since_last_dump;
  holdout_sum_loss = other.holdout_sum_loss;
  holdout_best_loss = other.holdout_best_loss;
  weighted_holdout_examples_since_last_pass = other.weighted_holdout_examples_since_last_pass;
  holdout_sum_loss_since_last_pass = other.holdout_sum_loss_since_last_pass;
  holdout_best_pass = other.holdout_best_pass;
  report_multiclass_log_loss = other.report_multiclass_log_loss;
  multiclass_log_loss = other.multiclass_log_loss;
  holdout_multiclass_log_loss = other.holdout_multiclass_log_loss;
  is_more_than_two_labels_observed = other.is_more_than_two_labels_observed;
  first_observed_label = other.first_observed_label;
  second_observed_label = other.second_observed_label;
}

shared_data& shared_data::operator=(const shared_data& other)
{
  if (this == &other) { return *this; }
  queries = other.queries;
  example_number = other.example_number;
  total_features = other.total_features;
  t = other.t;
  weighted_labeled_examples = other.weighted_labeled_examples;
  old_weighted_labeled_examples = other.old_weighted_labeled_examples;
  weighted_unlabeled_examples = other.weighted_unlabeled_examples;
  weighted_labels = other.weighted_labels;
  sum_loss = other.sum_loss;
  sum_loss_since_last_dump = other.sum_loss_since_last_dump;
  dump_interval = other.dump_interval;
  gravity = other.gravity;
  contraction = other.contraction;
  min_label = other.min_label;
  max_label = other.max_label;
  if (other.ldict) { ldict = VW::make_unique<VW::named_labels>(*other.ldict); }
  weighted_holdout_examples = other.weighted_holdout_examples;
  weighted_holdout_examples_since_last_dump = other.weighted_holdout_examples_since_last_dump;
  holdout_sum_loss_since_last_dump = other.holdout_sum_loss_since_last_dump;
  holdout_sum_loss = other.holdout_sum_loss;
  holdout_best_loss = other.holdout_best_loss;
  weighted_holdout_examples_since_last_pass = other.weighted_holdout_examples_since_last_pass;
  holdout_sum_loss_since_last_pass = other.holdout_sum_loss_since_last_pass;
  holdout_best_pass = other.holdout_best_pass;
  report_multiclass_log_loss = other.report_multiclass_log_loss;
  multiclass_log_loss = other.multiclass_log_loss;
  holdout_multiclass_log_loss = other.holdout_multiclass_log_loss;
  is_more_than_two_labels_observed = other.is_more_than_two_labels_observed;
  first_observed_label = other.first_observed_label;
  second_observed_label = other.second_observed_label;
  return *this;
}

shared_data::shared_data(shared_data&& other) noexcept
{
  queries = other.queries;
  example_number = other.example_number;
  total_features = other.total_features;
  t = other.t;
  weighted_labeled_examples = other.weighted_labeled_examples;
  old_weighted_labeled_examples = other.old_weighted_labeled_examples;
  weighted_unlabeled_examples = other.weighted_unlabeled_examples;
  weighted_labels = other.weighted_labels;
  sum_loss = other.sum_loss;
  sum_loss_since_last_dump = other.sum_loss_since_last_dump;
  dump_interval = other.dump_interval;
  gravity = other.gravity;
  contraction = other.contraction;
  min_label = other.min_label;
  max_label = other.max_label;
  ldict = std::move(other.ldict);
  weighted_holdout_examples = other.weighted_holdout_examples;
  weighted_holdout_examples_since_last_dump = other.weighted_holdout_examples_since_last_dump;
  holdout_sum_loss_since_last_dump = other.holdout_sum_loss_since_last_dump;
  holdout_sum_loss = other.holdout_sum_loss;
  holdout_best_loss = other.holdout_best_loss;
  weighted_holdout_examples_since_last_pass = other.weighted_holdout_examples_since_last_pass;
  holdout_sum_loss_since_last_pass = other.holdout_sum_loss_since_last_pass;
  holdout_best_pass = other.holdout_best_pass;
  report_multiclass_log_loss = other.report_multiclass_log_loss;
  multiclass_log_loss = other.multiclass_log_loss;
  holdout_multiclass_log_loss = other.holdout_multiclass_log_loss;
  is_more_than_two_labels_observed = other.is_more_than_two_labels_observed;
  first_observed_label = other.first_observed_label;
  second_observed_label = other.second_observed_label;
}

shared_data& shared_data::operator=(shared_data&& other) noexcept
{
  queries = other.queries;
  example_number = other.example_number;
  total_features = other.total_features;
  t = other.t;
  weighted_labeled_examples = other.weighted_labeled_examples;
  old_weighted_labeled_examples = other.old_weighted_labeled_examples;
  weighted_unlabeled_examples = other.weighted_unlabeled_examples;
  weighted_labels = other.weighted_labels;
  sum_loss = other.sum_loss;
  sum_loss_since_last_dump = other.sum_loss_since_last_dump;
  dump_interval = other.dump_interval;
  gravity = other.gravity;
  contraction = other.contraction;
  min_label = other.min_label;
  max_label = other.max_label;
  ldict = std::move(other.ldict);
  weighted_holdout_examples = other.weighted_holdout_examples;
  weighted_holdout_examples_since_last_dump = other.weighted_holdout_examples_since_last_dump;
  holdout_sum_loss_since_last_dump = other.holdout_sum_loss_since_last_dump;
  holdout_sum_loss = other.holdout_sum_loss;
  holdout_best_loss = other.holdout_best_loss;
  weighted_holdout_examples_since_last_pass = other.weighted_holdout_examples_since_last_pass;
  holdout_sum_loss_since_last_pass = other.holdout_sum_loss_since_last_pass;
  holdout_best_pass = other.holdout_best_pass;
  report_multiclass_log_loss = other.report_multiclass_log_loss;
  multiclass_log_loss = other.multiclass_log_loss;
  holdout_multiclass_log_loss = other.holdout_multiclass_log_loss;
  is_more_than_two_labels_observed = other.is_more_than_two_labels_observed;
  first_observed_label = other.first_observed_label;
  second_observed_label = other.second_observed_label;
  return *this;
}

double shared_data::weighted_examples() const { return weighted_labeled_examples + weighted_unlabeled_examples; }

void shared_data::update(bool test_example, bool labeled_example, float loss, float weight, size_t num_features)
{
  t += weight;
  if (test_example && labeled_example)
  {
    weighted_holdout_examples += weight;  // test weight seen
    weighted_holdout_examples_since_last_dump += weight;
    weighted_holdout_examples_since_last_pass += weight;
    holdout_sum_loss += loss;
    holdout_sum_loss_since_last_dump += loss;
    holdout_sum_loss_since_last_pass += loss;  // since last pass
  }
  else
  {
    if (labeled_example) { weighted_labeled_examples += weight; }
    else
    {
      weighted_unlabeled_examples += weight;
    }
    sum_loss += loss;
    sum_loss_since_last_dump += loss;
    total_features += num_features;
    example_number++;
  }
}

void shared_data::update_dump_interval(bool progress_add, float progress_arg)
{
  sum_loss_since_last_dump = 0.0;
  old_weighted_labeled_examples = weighted_labeled_examples;
  if (progress_add) { dump_interval = static_cast<float>(weighted_examples()) + progress_arg; }
  else
  {
    dump_interval = static_cast<float>(weighted_examples()) * progress_arg;
  }
}

// Column width, precision constants:
static constexpr int col_avg_loss = 8;
static constexpr int prec_avg_loss = 6;
static constexpr int col_since_last = 8;
static constexpr int prec_since_last = 6;
static constexpr int col_example_counter = 12;
static constexpr int col_example_weight = col_example_counter + 2;
static constexpr int prec_example_weight = 1;
static constexpr int col_current_label = 14;
static constexpr int prec_current_label = 4;
static constexpr int col_current_predict = 14;
static constexpr int prec_current_predict = 4;
static constexpr int col_current_features = 8;

static constexpr size_t num_cols = 7;
static constexpr std::array<VW::column_definition, num_cols> SD_HEADER_COLUMNS = {
    VW::column_definition(col_avg_loss, VW::align_type::left, VW::wrap_type::wrap_space),           // average loss
    VW::column_definition(col_since_last, VW::align_type::left, VW::wrap_type::wrap_space),         // since last
    VW::column_definition(col_example_counter, VW::align_type::right, VW::wrap_type::wrap_space),   // example counter
    VW::column_definition(col_example_weight, VW::align_type::right, VW::wrap_type::wrap_space),    // example weight
    VW::column_definition(col_current_label, VW::align_type::right, VW::wrap_type::wrap_space),     // current label
    VW::column_definition(col_current_predict, VW::align_type::right, VW::wrap_type::wrap_space),   // current predict
    VW::column_definition(col_current_features, VW::align_type::right, VW::wrap_type::wrap_space),  // current features
};
static constexpr std::array<VW::column_definition, num_cols> VALUE_COLUMNS = {
    VW::column_definition(col_avg_loss, VW::align_type::left, VW::wrap_type::truncate),          // average loss
    VW::column_definition(col_since_last, VW::align_type::left, VW::wrap_type::truncate),        // since last
    VW::column_definition(col_example_counter, VW::align_type::right, VW::wrap_type::truncate),  // example counter
    VW::column_definition(col_example_weight, VW::align_type::right, VW::wrap_type::truncate),   // example weight
    VW::column_definition(
        col_current_label, VW::align_type::right, VW::wrap_type::truncate_with_ellipsis),  // current label
    VW::column_definition(
        col_current_predict, VW::align_type::right, VW::wrap_type::truncate_with_ellipsis),       // current predict
    VW::column_definition(col_current_features, VW::align_type::right, VW::wrap_type::truncate),  // current features
};
static const std::array<std::string, num_cols> SD_HEADER_TITLES = {"average loss", "since last", "example counter",
    "example\nweight", "current\nlabel", "current\npredict", "current features"};

// progressive validation header
void shared_data::print_update_header(std::ostream& trace_message)
{
  format_row(SD_HEADER_TITLES, SD_HEADER_COLUMNS, 1, trace_message);
  trace_message << "\n";
}

template <typename T>
std::string num_to_fixed_string(T num, int decimal_precision)
{
  return fmt::format("{:.{}f}", num, decimal_precision);
}

void shared_data::print_update(std::ostream& output_stream, bool holdout_set_off, size_t current_pass, float label,
    float prediction, size_t num_features, bool progress_add, float progress_arg)
{
  std::ostringstream label_buf, pred_buf;

  if (label < FLT_MAX) { label_buf << num_to_fixed_string(label, prec_current_label); }
  else
  {
    label_buf << "unknown";
  }

  pred_buf << num_to_fixed_string(prediction, prec_current_predict);

  print_update(output_stream, holdout_set_off, current_pass, label_buf.str(), pred_buf.str(), num_features,
      progress_add, progress_arg);
}

void shared_data::print_update(std::ostream& output_stream, bool holdout_set_off, size_t current_pass, uint32_t label,
    uint32_t prediction, size_t num_features, bool progress_add, float progress_arg)
{
  std::ostringstream label_buf, pred_buf;

  if (label < INT_MAX) { label_buf << label; }
  else
  {
    label_buf << "unknown";
  }

  pred_buf << prediction;

  print_update(output_stream, holdout_set_off, current_pass, label_buf.str(), pred_buf.str(), num_features,
      progress_add, progress_arg);
}

void shared_data::print_update(std::ostream& output_stream, bool holdout_set_off, size_t current_pass,
    const std::string& label, uint32_t prediction, size_t num_features, bool progress_add, float progress_arg)
{
  std::ostringstream pred_buf;

  pred_buf << prediction;

  print_update(
      output_stream, holdout_set_off, current_pass, label, pred_buf.str(), num_features, progress_add, progress_arg);
}

void shared_data::print_update(std::ostream& output_stream, bool holdout_set_off, size_t current_pass,
    const std::string& label, const std::string& prediction, size_t num_features, bool progress_add, float progress_arg)
{
  bool holding_out = false;

  std::string avg_loss;
  std::string since_last;
  if (!holdout_set_off && current_pass >= 1)
  {
    if (holdout_sum_loss == 0. && weighted_holdout_examples == 0.) { avg_loss = "unknown"; }
    else
    {
      avg_loss = num_to_fixed_string(holdout_sum_loss / weighted_holdout_examples, prec_avg_loss);
    }

    if (holdout_sum_loss_since_last_dump == 0. && weighted_holdout_examples_since_last_dump == 0.)
    { since_last = "unknown"; }
    else
    {
      since_last = num_to_fixed_string(
          holdout_sum_loss_since_last_dump / weighted_holdout_examples_since_last_dump, prec_since_last);
    }

    weighted_holdout_examples_since_last_dump = 0;
    holdout_sum_loss_since_last_dump = 0.0;

    holding_out = true;
  }
  else
  {
    if (weighted_labeled_examples > 0.)
    { avg_loss = num_to_fixed_string(sum_loss / weighted_labeled_examples, prec_avg_loss); }
    else
    {
      avg_loss = "n.a.";
    }

    if (weighted_labeled_examples == old_weighted_labeled_examples) { since_last = "n.a."; }
    else
    {
      since_last = num_to_fixed_string(
          sum_loss_since_last_dump / (weighted_labeled_examples - old_weighted_labeled_examples), prec_since_last);
    }
  }

  format_row({avg_loss, since_last, std::to_string(example_number),
                 num_to_fixed_string(weighted_examples(), prec_example_weight), label, prediction,
                 std::to_string(num_features)},
      VALUE_COLUMNS, 1, output_stream);

  if (holding_out) { output_stream << " h"; }
  output_stream << std::endl;
  update_dump_interval(progress_add, progress_arg);
}

void shared_data::print_summary(std::ostream& output, const shared_data& sd, const loss_function& loss_func,
    uint64_t current_pass, bool holdout_set_off) const
{
  auto saved_precision = output.precision();
  output.precision(6);
  output << std::fixed;
  output << std::endl << "finished run";
  if (current_pass == 0 || current_pass == 1) { output << std::endl << "number of examples = " << sd.example_number; }
  else
  {
    output << std::endl << "number of examples per pass = " << sd.example_number / current_pass;
    output << std::endl << "passes used = " << current_pass;
  }
  output << std::endl << "weighted example sum = " << sd.weighted_examples();
  output << std::endl << "weighted label sum = " << sd.weighted_labels;
  output << std::endl << "average loss = ";
  if (holdout_set_off)
  {
    if (sd.weighted_labeled_examples > 0) { output << sd.sum_loss / sd.weighted_labeled_examples; }
    else
    {
      output << "n.a.";
    }
  }
  else if ((sd.holdout_best_loss == FLT_MAX) || (sd.holdout_best_loss == FLT_MAX * 0.5))
  {
    output << "undefined (no holdout)";
  }
  else
  {
    output << sd.holdout_best_loss << " h";
  }
  if (sd.report_multiclass_log_loss)
  {
    if (holdout_set_off)
    {
      output << std::endl << "average multiclass log loss = " << sd.multiclass_log_loss / sd.weighted_labeled_examples;
    }
    else
    {
      output << std::endl
             << "average multiclass log loss = " << sd.holdout_multiclass_log_loss / sd.weighted_labeled_examples
             << " h";
    }
  }

  float best_constant;
  float best_constant_loss;
  if (VW::get_best_constant(loss_func, sd, best_constant, best_constant_loss))
  {
    output << std::endl << "best constant = " << best_constant;
    if (best_constant_loss != FLT_MIN) { output << std::endl << "best constant's loss = " << best_constant_loss; }
  }

  output << std::endl << "total feature number = " << sd.total_features;
  if (sd.queries > 0) { output << std::endl << "total queries = " << sd.queries; }
  output << std::endl;

  output.precision(saved_precision);
}