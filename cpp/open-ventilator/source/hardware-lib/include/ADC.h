
/**
 *  @file: ADC.h
 *
 *  Alarm Buzzer control
 * 
 *  Copyright (C) 2020  Joe Turner <joe@agavemountain.com>
 *
 *     This program is distributed in the hope that it will be useful,
 *     but WITHOUT ANY WARRANTY; without even the implied warranty of
 *     MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *     GNU General Public License for more details.
 *
 *     You should have received a copy of the GNU General Public License
 *     along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */
#pragma once

/**
 * The ST10F276E has 16+8 multiplexed input channels on Port 5 and Port 1. The selection
 * between Port 5 and Port 1 is made via a bit in a XBus register. Refer to the user manual for
 * a detailed description.
 * A different accuracy is guaranteed (Total Unadjusted Error) on Port 5 and Port 1 analog
 * channels (with higher restrictions when overload conditions occur); in particular, Port 5
 * channels are more accurate than the Port 1 ones. 
 */

