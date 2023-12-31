// Copied from https://github.com/Leont/libperl-- and modified by Elliot C.
// Edwards to remove the Boost dependency (trivial, since every Boost feature
// that the library depended on has been incorporated into the C++ standard).
//
// Although the README for the tap++ module references a LICENSE file, no such
// file exists in the repository.
//
// The README for Leont/libperl-- contains the following notice:
//
// ```
// COPYRIGHT AND LICENCE
//
// Copyright (C) 2007, 2008, 2009, 2010 Leon Timmermans
// This program is free software; you can redistribute it and/or modify it
// under the same terms as Perl itself.
// ```
//
// Perl may be redistributed under either the GNU General Public License,
// version 1 or later, or under the "Artistic License" (see
// <https://dev.perl.org/licenses/>). Since the current project (c-thedral) is
// distributed under GPLv3, I have elected to redistribute libtap++ under the
// same license.
//
// Accordingly:
//
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 3, or (at your option)
// any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program; if not, see <https://www.gnu.org/licenses>.

#define WANT_TEST_EXTRAS
#include <cstdlib>
#include <stack>
#include <string>
#include <tap++/tap++.h>

namespace TAP {
std::string TODO;

const details::skip_all_type skip_all = details::skip_all_type();
const details::no_plan_type no_plan   = details::no_plan_type();

namespace {
unsigned expected = 0;
unsigned counter  = 0;
unsigned not_oks  = 0;

std::string
todo_test()
{
        if (TODO.empty()) {
                return TODO;
        }
        return " # TODO " + TODO;
}

bool
is_todo_test() noexcept
{
        return !TODO.empty();
}

bool is_planned      = false;
bool no_planned      = false;
bool has_output_plan = false;

void
output_plan(unsigned tests, const std::string &extra = "")
{
        if (has_output_plan) {
                throw fatal_exception("Can't plan twice");
        }
        *details::output << "1.." << tests << extra << std::endl;
        has_output_plan = true;
}
inline std::string
to_string(unsigned num)
{
        return std::to_string(num);
}

inline void
_done_testing(unsigned tests)
{
        static bool is_done = false;
        if (is_done) {
                fail("done_testing() was already called");
                return;
        }
        is_done = true;

        if ((expected != 0U) && tests != expected) {
                fail(std::string("planned to run ") + to_string(expected) +
                     " tests but done_testing() expects " + to_string(tests));
        }
        else {
                expected = tests;
        }
        is_planned = true;
        if (!has_output_plan) {
                output_plan(tests);
        }
}

} // namespace

void
plan(unsigned tests)
{
        if (is_planned) {
                bail_out("Can't plan again!");
        }
        is_planned = true;
        output_plan(tests);
        expected = tests;
}
void
plan(const details::skip_all_type & /*unused*/, const std::string &reason)
{
        output_plan(0, " #skip " + reason);
        std::exit(0);
}
void
plan(const details::no_plan_type & /*unused*/)
{
        is_planned = true;
        no_planned = true;
}

void
done_testing()
{
        _done_testing(encountered());
}

void
done_testing(unsigned tests)
{
        no_planned = false;
        _done_testing(tests);
}

unsigned
planned()
{
        return expected;
}
unsigned
encountered()
{
        return counter;
}

int
exit_status()
{
        //		bool passing;
        if (!is_planned && (encountered() != 0U)) {
                diag("Tests were run but no plan was declared and "
                     "done_testing() was not seen.");
        }
        if (no_planned) {
                output_plan(encountered());
                return static_cast<int>(std::min(254U, not_oks));
        }
        if (expected == counter) {
                return static_cast<int>(std::min(254U, not_oks));
        }
        return 255;
}
bool
summary()
{
        return not_oks != 0U;
}

void
bail_out(const std::string &reason)
{
        *details::output << "Bail out!  " << reason << std::endl;
        std::exit(255); // Does not unwind stack!
}

bool
ok(bool is_ok, const std::string &message)
{
        const char *hot_or_not = is_ok ? "" : "not ";
        *details::output << hot_or_not << "ok " << ++counter << " - " << message
                         << todo_test() << std::endl;
        if (!is_ok && !is_todo_test()) {
                ++not_oks;
        }
        return is_ok;
}
bool
not_ok(bool is_not_ok, const std::string &message)
{
        return !ok(!is_not_ok, message);
}

bool
pass(const std::string &message)
{
        return ok(true, message);
}
bool
fail(const std::string &message)
{
        return ok(false, message);
}

void
skip(unsigned num, const std::string &reason)
{
        for (unsigned i = 0; i < num; ++i) {
                pass(" # skip " + reason);
        }
}

void
set_output(std::ostream &new_output)
{
        if (is_planned) {
                throw fatal_exception("Can't set output after plan()");
        }
        details::output = &new_output;
}
void
set_error(std::ostream &new_error)
{
        if (is_planned) {
                throw fatal_exception("Can't set error after plan()");
        }
        details::error = &new_error;
}
todo_guard::todo_guard() : value(TODO) {}
todo_guard::~todo_guard() { TODO = value; }
namespace details {
std::ostream *output = &std::cout;
std::ostream *error  = &std::cout;
static std::stack<unsigned> block_expected;
void
start_block(unsigned expected)
{
        block_expected.push(encountered() + expected);
}
unsigned
stop_block()
{
        unsigned ret = block_expected.top();
        block_expected.pop();
        return ret;
}

char const *
failed_test_msg() noexcept
{
        return is_todo_test() ? "Failed (TODO) test" : "Failed test";
}

} // namespace details

void
skip(const std::string &reason)
{
        throw details::Skip_exception(reason);
}
void
skip_todo(const std::string &reason)
{
        throw details::Todo_exception(reason);
}

} // namespace TAP
