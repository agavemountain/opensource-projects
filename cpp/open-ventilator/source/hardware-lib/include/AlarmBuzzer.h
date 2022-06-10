/**
 *  @file: AlarmBuzzer.h
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
 * Two alarm buzzers are located on the buzzer PCBA. The buzzer PCBA is capable 
 * of producing 65 - 80 dBA alarm tones based on the alarm priority. 
 * A 4.8 V Ni-MH battery is mounted on the buzzer PCBA to power the ventilator’s 
 * POWER SUPPLY LOSS alarm. The battery is charged to a maximum voltage of 5.6 V. 
 * At this point the charger switches to a trickle-charge mode which maintains 
 * the battery voltage.
 */