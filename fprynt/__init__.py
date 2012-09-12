# License & Copyright
# ===================
#
# Copyright 2012 Christopher M Poole
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <http://www.gnu.org/licenses/>.


from libfprynt import Reader


class _fingers:
    def __init__(self):
        fingers = ["LeftThumb", "LeftIndex", "LeftMiddle",
                   "LeftRing", "LeftLittle", "RightThumb",
                   "RightIndex", "RightMiddle", "RightRing",
                   "RightLittle"]

        for i, f in enumerate(fingers):
            setattr(self, f, i+1)

    def __iter__(self):
        return iter(range(1, 11))

Fingers = _fingers()

